#pragma once

#include <sstream>
#include <string>

struct SKP_IF_EQUALS {
  int reg_addr;
  int val;
  std::string str() const {
    std::stringstream ss;
    ss << "SKP_IF_REG_ADDR_EQUALS[" << reg_addr << " " << val << "]";
    return ss.str();
  }
};
