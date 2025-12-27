#pragma once

#include <sstream>
#include <string>

struct BCD_STORE {
  int target;
  std::string str() const {
    std::stringstream ss;
    ss << "BCD_STORE[" << target << "]";
    return ss.str();
  }
};
