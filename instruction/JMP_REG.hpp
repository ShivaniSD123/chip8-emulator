#pragma once

#include <sstream>
#include <string>

struct JMP_REG {
  int addr;
  std::string str() const {
    std::stringstream ss;
    ss << "JMP_REG[" << addr << "]";
    return ss.str();
  }
};
