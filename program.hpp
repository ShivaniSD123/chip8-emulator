#pragma once

#include <vector>

#include "instruction/instruction.hpp"

class Program {
  std::vector<uint8_t> bytes;

public:
  Program(std::vector<uint8_t> bytes) : bytes(std::move(bytes)) {}

  Instruction instruction_at(int addr) {
    uint16_t instruction_bits = (bytes[addr] << 8 | bytes[addr + 1]);
    Instruction i = parse_instruction_bits(instruction_bits);
    return i;
  }
};
