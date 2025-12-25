#pragma once

#include <vector>

#include "common.hpp"
#include "instruction/instruction.hpp"
#include "program.hpp"

class Interpreter {
  Program program;
  bool is_running_;
  int pc;
  std::vector<int> video_buffer;
  std::stack<int> stack;
  std::vector<int> registers;

 public:
  Interpreter(Program p)
      : program(std::move(p)), pc(0), video_buffer(64, 0), registers(16, -1) {
    is_running_ = true;
  }
  struct instruction_executor {
    Interpreter& self;
    void operator()(CLS x) {
      std::fill(self.video_buffer.begin(), self.video_buffer.end(), 0);
    }

    void operator()(Return x) {
      precondition(!self.stack.empty(),
                   "Return should not be called without calling a function");
      int address = self.stack.top();
      self.stack.pop();
      self.pc = address;
    }

    void operator()(JMP_ADDR x) { self.pc = self.toCodePointer(x.address); }

    void operator()(CALL_SUB x) {
      self.stack.push(self.pc);
      self.pc = x.address;
    }

    void operator()(JMP_REG x) {
      int index = x.address + self.registers[0];
      self.pc = index;
    }

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

    template <typename T>
    void operator()(T) {}
  };

  /// Returns true if program is running
  bool is_running() const { return is_running_; }

  /// Executes the next instruction of program.
  void step() {
    Instruction i = current_instruction();
    advance_program_counter();
    execute(i);
  }

 private:
  /// The current instruction.
  Instruction current_instruction() { return program.instruction_at(pc); }

  /// Advances the program counter to next instruction.
  void advance_program_counter() { pc += 2; }

  void execute(Instruction i) {
    std::visit(overloaded{
                   [](Unknown) {},
                   [](auto x) { std::cout << x.str() << std::endl; },
               },
               i);
    std::visit(instruction_executor{*this}, i);
  }

  int toCodePointer(int address) { return address - 0x200; }
};