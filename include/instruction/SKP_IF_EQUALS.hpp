#pragma once

#include <sstream>
#include <string>

struct SKP_IF_EQUALS {
  int target;
  int val;

  std::string str() const {
    std::stringstream ss;
    ss << "SKP_IF_REG_ADDR_EQUALS[" << target << " " << val << "]";
    return ss.str();
  }
};
