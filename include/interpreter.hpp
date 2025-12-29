#pragma once

#include <array>
#include <bitset>
#include <vector>

#include "common.hpp"
#include "font.hpp"
#include "instruction/instruction.hpp"
#include "program.hpp"

class Interpreter {
  Program program;
  Font font;

  struct code_pointer {
    int raw_address;
  };

  std::vector<uint8_t> ram;
  code_pointer pc;

  std::stack<code_pointer> stack;
  std::vector<int> registers;
  code_pointer index_register;
  int delay_timer;

  /// Load ROM file in RAM
  void load_rom() {
    for (int i = 0; i < program.bytes.size(); i++) {
      ram[0x200 + i] = program.bytes[i];
    }
  }

  /// Load font in RAM
  void load_font() {
    for (int i = 0; i < font.chip8_font.size(); i++) {
      ram[0x050 + i] = font.chip8_font[i];
    }
  }

 public:
  std::vector<std::vector<int>> video_buffer;
  std::array<bool, 16> keypad;

  Interpreter(Program p, Font f)
      : program(std::move(p)),
        font(std::move(f)),
        pc({0x200}),
        video_buffer(32, std::vector<int>(64, 0)),
        registers(16, 0),
        ram(4096),
        delay_timer(0) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    load_rom();
    load_font();
    std::fill(keypad.begin(), keypad.end(), false);
  }

  struct instruction_executor {
    Interpreter& self;

    void operator()(CLS x) {
      for (auto& r : self.video_buffer)
        std::fill(r.begin(), r.end(), 0);
    }

    void operator()(Return x) {
      precondition(!self.stack.empty(),
                   "Return should not be called without calling a function");
      auto returnAddress = self.stack.top();
      self.stack.pop();
      self.pc = returnAddress;
    }

    void operator()(JMP_ADDR x) { self.pc = {x.address}; }

    void operator()(CALL_SUB x) {
      self.stack.push(self.pc);
      self.pc = {x.address};
    }

    void operator()(JMP_REG x) { self.pc = {x.address + self.registers[0]}; }

    void operator()(SKP_IF_EQUALS x) {
      if (self.registers[x.target_register] == x.val)
        self.advance_program_counter();
    }

    void operator()(SKP_NOT_EQUALS x) {
      if (self.registers[x.target_register] != x.val)
        self.advance_program_counter();
    }

    void operator()(SKP_REG_EQUALS x) {
      int r1 = x.first_register;
      int r2 = x.second_register;
      if (self.registers[r1] == self.registers[r2])
        self.advance_program_counter();
    }

    void operator()(SKP_REG_NOT_EQUALS x) {
      int r1 = x.first_register;
      int r2 = x.second_register;
      if (self.registers[r1] != self.registers[r2])
        self.advance_program_counter();
    }

    void operator()(REG_VAL_ASSIGN x) {
      self.registers[x.target_register] = x.val;
    }

    void operator()(REG_VAL_INC x) {
      int address = x.target_register;
      self.registers[address] += x.val;
    }

    void operator()(REG_ASSIGN x) {
      self.registers[x.to_register] = self.registers[x.from_register];
    }

    void operator()(OR x) {
      self.registers[x.first_register] |= self.registers[x.second_register];
    }

    void operator()(AND x) {
      self.registers[x.first_register] &= self.registers[x.second_register];
    }

    void operator()(XOR x) {
      self.registers[x.first_register] ^= self.registers[x.second_register];
    }

    void operator()(ADD x) {
      int r1 = x.first_register;
      int r2 = x.second_register;
      int sum = self.registers[r1] + self.registers[r2];
      self.registers[15] = (sum > 255);
      self.registers[r1] = sum & 0xFF;
    }

    void operator()(SUB x) {
      int r1 = x.first_register;
      int r2 = x.second_register;
      int sub = self.registers[r1] - self.registers[r2];
      self.registers[15] = (self.registers[r1] >= self.registers[r2]);
      self.registers[r1] = sub & 0xFF;
    }

    void operator()(SHR x) {
      self.registers[15] = self.registers[x.target_register] & 0x0001;
      self.registers[x.target_register] >>= 1;
    }

    void operator()(SUBN x) {
      int val1 = self.registers[x.first_register];
      int val2 = self.registers[x.second_register];
      self.registers[15] = (val2 >= val1);
      self.registers[x.first_register] = val2 - val1;
    }

    void operator()(SHL x) {
      self.registers[15] = (self.registers[x.target_register] & 0x80) >> 7;
      self.registers[x.target_register] <<= 1;
    }

    void operator()(IND_ASSIGN x) { self.index_register = {x.address}; }

    void operator()(IND_INC x) {
      self.index_register = {self.index_register.raw_address +
                             self.registers[x.target_register]};
    }

    void operator()(FT_SPT_ADDR x) {
      self.index_register = {0x050 + self.registers[x.target_register] * 5};
    }

    void operator()(BCD_STORE x) { self.storeBCD(x.target_register); }

    void operator()(STR_REG_MEM x) {
      for (int i = 0; i <= x.target_register; i++) {
        self.ram[self.index_register.raw_address + i] = self.registers[i];
      }
    }

    void operator()(LD_REG_MEM x) {
      for (int i = 0; i <= x.until_register; i++) {
        self.registers[i] = self.ram[self.index_register.raw_address + i];
      }
    }

    void operator()(DRW_SPRITE x) {
      self.registers[15] = 0;

      for (int i = 0; i < x.val; i++) {
        uint8_t sprite = self.ram[self.index_register.raw_address + i];
        std::bitset<8> bits(sprite);

        for (int j = 0; j < 8; j++) {
          if (!bits[7 - j])
            continue;

          int y = (self.registers[x.y_register] + i) % 32;
          int xcoord = (self.registers[x.x_register] + j) % 64;

          if (self.video_buffer[y][xcoord])
            self.registers[15] = 1;

          self.video_buffer[y][xcoord] ^= 1;
        }
      }
    }

    void operator()(SKP_KEY_NOT_PRESS x) {
      if (!self.keypad[self.registers[x.target_register]])
        self.advance_program_counter();
    }

    void operator()(SKP_KEY_PRESS x) {
      if (self.keypad[self.registers[x.target_register]])
        self.advance_program_counter();
    }

    void operator()(GET_DELAY_TIMER x) {
      self.registers[x.target_register] = self.delay_timer;
    }

    void operator()(WT_KEY_PRESS x) {
      bool pressed = false;
      for (int i = 0; i < 16; i++) {
        if (self.keypad[i]) {
          pressed = true;
          self.registers[x.target_register] = i;
          std::fill(std::begin(self.keypad), std::end(self.keypad), false);
          break;
        }
      }
      if (!pressed)
        self.pc.raw_address -= 2;
    }

    void operator()(RAND x) {
      uint8_t r = std::rand() & 0xFF;
      self.registers[x.target_register] = r & x.mask;
    }

    void operator()(SET_DELAY_TIMER x) {
      self.delay_timer = self.registers[x.target_register];
    }

    void operator()(SET_SOUND_TIMER) {}

    void operator()(NOP) {}

    void operator()(Unknown x) {
      precondition_failure("Unknown instruction[" + x.str() +
                           "] should not be reachable!");
    }
  };

  /// Executes the next instruction of program.
  void step() {
    Instruction i = current_instruction();
    advance_program_counter();
    execute(i);
    print_instruction(i);
  }

  //Tick timer;
  void tick_timer() {
    if (delay_timer > 0)
      delay_timer--;
    std::cout << "delay timer " << delay_timer << std::endl;
  }

 private:
  /// The current instruction.
  Instruction current_instruction() {
    uint16_t b1 = ram[pc.raw_address];
    uint16_t b2 = ram[pc.raw_address + 1];
    return parse_instruction_bits((b1 << 8) | b2);
  }

  /// Advances the program counter to next instruction.
  void advance_program_counter() { pc.raw_address += 2; }

  /// Returns font sprite address
  code_pointer get_fontspite_address(int x) { return {0x050 + (x * 5)}; }

  /// Stores the bcd digits
  void storeBCD(int x) {
    x = registers[x];
    ram[index_register.raw_address] = x / 100;
    ram[index_register.raw_address + 1] = (x / 10) % 10;
    ram[index_register.raw_address + 2] = x % 10;
  }

  void print_instruction(Instruction i) {
    std::visit(overloaded{[&](auto x) { std::cout << x.str() << std::endl; }},
               i);
  }

  void clear_screen() const { system("clear"); }

  void execute(Instruction i) { std::visit(instruction_executor{*this}, i); }
};