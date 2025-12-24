#pragma once

#include <sstream>
#include <string>

struct SKP_NOT_EQUALS {
  int reg_addr;
  int val;
  std::string str() const {
    std::stringstream ss;
    ss << "SKP_NOT_EQUALS[" << reg_addr << " " << val << "]";
    return ss.str();
  }
};
