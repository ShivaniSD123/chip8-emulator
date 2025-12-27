#pragma once

#include <sstream>
#include <string>

struct LD_REG_MEM {
  int target;
  std::string str() const {
    std::stringstream ss;
    ss << "LD_REG_MEM[" << target << "]";
    return ss.str();
  }
};
