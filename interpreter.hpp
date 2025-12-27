#pragma once

#include <bitset>
#include <random>
#include <thread>
#include <vector>

#include "common.hpp"
#include "font.hpp"
#include "graphic_design.hpp"
#include "instruction/instruction.hpp"
#include "program.hpp"

class Interpreter {
  Program program;
  Font font;
  bool is_running_;
  struct code_pointer {
    int raw_address;
  };
  Display display;
  std::vector<uint8_t> ram;
  code_pointer pc;
  std::vector<std::vector<int> > video_buffer;
  std::stack<code_pointer> stack;
  std::vector<int> registers;
  code_pointer index_register;
  std::ofstream log;

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
  Interpreter(Program p, Font f)
      : program(std::move(p)),
        font(std::move(f)),
        pc({0x200}),
        video_buffer(32, std::vector<int>(64, 0)),
        registers(16, 0),
        ram(4096),
        log("build/log.txt") {
    srand(time(NULL));
    is_running_ = true;
    load_rom();
    load_font();
  }

  struct instruction_executor {
    Interpreter& self;
    void operator()(CLS x) {
      for (auto& r : self.video_buffer) std::fill(r.begin(), r.end(), 0);
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
      if (self.registers[x.target] == x.val) self.advance_program_counter();
    }

    void operator()(SKP_NOT_EQUALS x) {
      if (self.registers[x.target] != x.val) self.advance_program_counter();
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

    void operator()(REG_VAL_ASSIGN x) { self.registers[x.target] = x.val; }

    void operator()(REG_VAL_INC x) {
      int address = x.target;
      self.registers[address] += x.val;
    }

    void operator()(REG_ASSIGN x) {
      self.registers[x.to] = self.registers[x.from];
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
      if (sum > 256)
        self.registers[15] = 1;
      else
        self.registers[15] = 0;
      self.registers[r1] = sum & 0x00ff;
    }

    void operator()(SUB x) {
      int r1 = x.first_register;
      int r2 = x.second_register;
      int sub = self.registers[r1] - self.registers[r2];
      if (self.registers[r1] > self.registers[r2])
        self.registers[15] = 1;
      else
        self.registers[15] = 0;
      self.registers[r1] = sub;
    }

    void operator()(SHR x) {
      self.registers[15] = self.registers[x.first_register] & 0x0001;
      self.registers[x.first_register] >>= 1;
    }

    void operator()(SUBN x) {
      int val1 = self.registers[x.first_register];
      int val2 = self.registers[x.second_register];
      self.registers[15] = (val2 >= val1);
      self.registers[x.first_register] = val2 - val1;
    }

    void operator()(SHL x) {
      self.registers[15] = self.registers[x.first_register] & 0x0080;
      self.registers[x.first_register] <<= 1;
    }

    void operator()(IND_ASSIGN x) { self.index_register = {x.ind_addr}; }

    void operator()(IND_INC x) {
      self.index_register = {x.target + self.index_register.raw_address};
    }

    void operator()(FT_SPT_ADDR x) { self.index_register = {x.target}; }

    void operator()(BCD_STORE x) { self.storeBCD(x.target); }

    void operator()(STR_REG_MEM x) {
      for (int i = 0; i <= x.target; i++) {
        self.ram[self.index_register.raw_address + i] = self.registers[i];
      }
    }

    void operator()(LD_REG_MEM x) {
      for (int i = 0; i <= x.target; i++) {
        self.registers[i] = self.ram[self.index_register.raw_address + i];
      }
    }

    void operator()(DRW_SPRITE x) {
      for (int i = 0; i < x.val; i++) {
        uint8_t spirit = self.ram[self.index_register.raw_address + i];
        std::bitset<8> bits(spirit);
        for (int j = 0; j <= 7; j++) {
          if (bits[7 - j] == 0) continue;
          if (self.video_buffer[(x.second_register + i) % 32]
                               [(x.first_register + j) % 64] == 1)
            self.registers[15] = 1;
          self.video_buffer[(x.second_register + i) % 32]
                           [(x.first_register + j) % 64] ^= 1;
        }
      }
    }

    void operator()(SKP_KEY_NOT_PRESS) {
      if (!self.random_bool()) {
        self.advance_program_counter();
      }
    }

    void operator()(SKP_KEY_PRESS) {
      if (self.random_bool()) {
        self.advance_program_counter();
      }
    }

    void operator()(GET_DELAY_TIMER x) {
      self.registers[x.target_register] = self.random_u8();
    }
    template <typename T>
    void operator()(T) {}

    void operator()(Unknown) {
      precondition("Unknown instruction should not be reachable!");
    }
  };

  /// Returns true if program is running
  bool is_running() const { return is_running_; }

  /// Executes the next instruction of program.
  void step() {
    Instruction i = current_instruction();
    advance_program_counter();
    execute(i);
    // clear_screen();
    // print_instruction(i);
    // print_screen();
    // std::this_thread::sleep_for(std::chrono::milliseconds(20));
    display.draw_screen(video_buffer);
    display.add_delay();
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

  void print_screen() const {
    for (int i = 0; i < 32; ++i) {
      for (int j = 0; j < 64; ++j) {
        if (video_buffer[i][j])
          std::cout << "█";
        else
          std::cout << " ";
      }
      std::cout << std::endl;
    }
  }

  void print_instruction(Instruction i) {
    std::visit(
        overloaded{
            [&](auto x) {
              std::cout << x.str() << std::endl;
              log << x.str() << std::endl;
            },
        },
        i);
  }

  void clear_screen() const { system("clear"); }

  void execute(Instruction i) { std::visit(instruction_executor{*this}, i); }

  bool random_bool() { return rand() % 2; }

  uint8_t random_u8() { return rand() % 256; }
};