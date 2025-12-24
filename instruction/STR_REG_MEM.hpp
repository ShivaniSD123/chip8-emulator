#pragma once

#include <sstream>
#include <string>

struct STR_REG_MEM {
  int reg_addr;
  std::string str() const {
    std::stringstream ss;
    ss << "STR_REG_MEM[" << reg_addr << "]";
    return ss.str();
  }
};
