#pragma once

#include <sstream>
#include <string>

struct LD_REG_MEM {
  int reg_addr;
  std::string str() const {
    std::stringstream ss;
    ss << "LD_REG_MEM[" << reg_addr << "]";
    return ss.str();
  }
};
