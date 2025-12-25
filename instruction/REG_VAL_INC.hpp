#pragma once

#include <sstream>
#include <string>

struct REG_VAL_INC {
  int target;
  int val;
  std::string str() const {
    std::stringstream ss;
    ss << "REG_VAL_INC[" << target << " " << val << "]";
    return ss.str();
  }
};
