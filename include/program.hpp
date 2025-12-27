#pragma once

#include <vector>

#include "instruction/instruction.hpp"

class Program {
 public:
  std::vector<uint8_t> bytes;

  Program(std::vector<uint8_t> bytes) : bytes(std::move(bytes)) {}

  Instruction instruction_at(int address) {
    uint16_t instruction_bits = (bytes[address] << 8 | bytes[address + 1]);
    Instruction i = parse_instruction_bits(instruction_bits);
    return i;
  }
};
