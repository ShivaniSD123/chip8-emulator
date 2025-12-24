#pragma once

#include <sstream>
#include <string>

struct XOR {
  int reg1_addr;
  int reg2_addr;
  std::string str() const {
    std::stringstream ss;
    ss << "XOR[" << reg1_addr << " " << reg2_addr << "]";
    return ss.str();
  }
};
