#pragma once

#include "instruction/instruction.hpp"
#include "program.hpp"

class Interpreter {
  Program program;

 public:
  Interpreter(Program p) : program(std::move(p)) {}

  /// Executes the next instruction of program.
  /// Returns true iff there was some instruction to execute.
  bool step() { return false; }
};