#pragma once

#include <sstream>
#include <string>

struct SKP_REG_NOT_EQUALS {
  int reg1_addr;
  int reg2_addr;
  std::string str() const {
    std::stringstream ss;
    ss << "SKP_REG_NOT_EQUALS[" << reg1_addr << " " << reg2_addr << "]";
    return ss.str();
  }
};
