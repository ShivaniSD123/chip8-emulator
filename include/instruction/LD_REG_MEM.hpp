#pragma once

#include <sstream>
#include <string>

struct LD_REG_MEM {
  int until_register;

  std::string str() const {
    std::stringstream ss;
    ss << "LD_REG_MEM[" << until_register << "]";
    return ss.str();
  }
};
