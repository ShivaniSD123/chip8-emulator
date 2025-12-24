#pragma once

#include <sstream>
#include <string>

struct REG_ASSIGN {
  int reg1_addr;
  int reg2_addr;
  std::string str() const {
    std::stringstream ss;
    ss << "REG_ASSIGN[" << reg1_addr << " " << reg2_addr << "]";
    return ss.str();
  }
};
