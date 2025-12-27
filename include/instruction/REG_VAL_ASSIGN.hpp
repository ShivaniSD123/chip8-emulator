#pragma once

#include <sstream>
#include <string>

struct REG_VAL_ASSIGN {
  int target;
  int val;
  std::string str() const {
    std::stringstream ss;
    ss << "REG_VAL_ASSIGN[" << target << " " << val << "]";
    return ss.str();
  }
};
