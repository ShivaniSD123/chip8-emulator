#pragma once

#include <sstream>
#include <string>

struct SKP_NOT_EQUALS {
  int target_register;
  int val;

  std::string str() const {
    std::stringstream ss;
    ss << "SKP_NOT_EQUALS[" << target_register << " " << val << "]";
    return ss.str();
  }
};
