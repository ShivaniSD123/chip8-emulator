#pragma once

#include <sstream>
#include <string>

struct SKP_NOT_EQUALS {
  int target;
  int val;
  std::string str() const {
    std::stringstream ss;
    ss << "SKP_NOT_EQUALS[" << target << " " << val << "]";
    return ss.str();
  }
};
