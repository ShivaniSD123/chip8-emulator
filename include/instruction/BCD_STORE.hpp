#pragma once

#include <sstream>
#include <string>

struct BCD_STORE {
  int target_register;

  std::string str() const {
    std::stringstream ss;
    ss << "BCD_STORE[" << target_register << "]";
    return ss.str();
  }
};
