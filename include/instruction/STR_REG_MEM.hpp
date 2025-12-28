#pragma once

#include <sstream>
#include <string>

struct STR_REG_MEM {
  int target_register;

  std::string str() const {
    std::stringstream ss;
    ss << "STR_REG_MEM[" << target_register << "]";
    return ss.str();
  }
};
