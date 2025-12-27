#pragma once

#include <sstream>
#include <string>

struct IND_INC {
  int target;
  std::string str() const {
    std::stringstream ss;
    ss << "IND_REG_INC[" << target << "]";
    return ss.str();
  }
};
