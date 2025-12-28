#pragma once

#include <sstream>
#include <string>

struct REG_VAL_INC {
  int target_register;
  int val;

  std::string str() const {
    std::stringstream ss;
    ss << "REG_VAL_INC[" << target_register << " " << val << "]";
    return ss.str();
  }
};
