#pragma once

#include <sstream>
#include <string>

struct BCD_STORE {
  int reg_addr;
  std::string str() const {
    std::stringstream ss;
    ss << "BCD_STORE[" << reg_addr << "]";
    return ss.str();
  }
};
