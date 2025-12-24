#pragma once

#include <sstream>
#include <string>

struct DRW_SPRITE {
  int reg1_addr;
  int reg2_addr;
  int val;
  std::string str() const {
    std::stringstream ss;
    ss << "DRW_SPRITE[" << reg1_addr << " " << reg2_addr << " " << val << "]";
    return ss.str();
  }
};
