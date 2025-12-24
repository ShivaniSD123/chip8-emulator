#pragma once

#include <sstream>
#include <string>

struct AND {
  int reg1_addr;
  int reg2_addr;
  std::string str() const {
    std::stringstream ss;
    ss << "AND[" << reg1_addr << " " << reg2_addr << "]";
    return ss.str();
  }
};
