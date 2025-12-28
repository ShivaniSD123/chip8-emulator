#pragma once

#include <sstream>
#include <string>

struct IND_INC {
  int target_register;

  std::string str() const {
    std::stringstream ss;
    ss << "IND_INC[" << target_register << "]";
    return ss.str();
  }
};
