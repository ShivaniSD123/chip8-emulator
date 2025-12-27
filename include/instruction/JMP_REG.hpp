#pragma once

#include <sstream>
#include <string>

struct JMP_REG {
  int address;

  std::string str() const {
    std::stringstream ss;
    ss << "JMP_REG[" << address << "]";
    return ss.str();
  }
};
