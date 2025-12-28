#pragma once

#include <sstream>
#include <string>

struct SHL {
  int target_register;

  std::string str() const {
    std::stringstream ss;
    ss << "SHL[" << target_register << "]";
    return ss.str();
  }
};
