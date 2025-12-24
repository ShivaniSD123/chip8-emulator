#pragma once

#include <sstream>
#include <string>

struct REG_VAL_ASSIGN {
  int reg_addr;
  int val;
  std::string str() const {
    std::stringstream ss;
    ss << "REG_VAL_ASSIGN[" << reg_addr << " " << val << "]";
    return ss.str();
  }
};
