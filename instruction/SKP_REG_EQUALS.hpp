#pragma once

#include <sstream>
#include <string>

struct SKP_REG_EQUALS {
  int reg1_addr;
  int reg2_addr;
  std::string str() const {
    std::stringstream ss;
    ss << "SKP_IF_REG_VAL_EQUALS[" << reg1_addr << " " << reg2_addr << "]";
    return ss.str();
  }
};
