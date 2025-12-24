#pragma once

#include <sstream>
#include <string>

struct IND_INC {
  int reg_addr;
  std::string str() const {
    std::stringstream ss;
    ss << "IND_REG_INC[" << reg_addr << "]";
    return ss.str();
  }
};
