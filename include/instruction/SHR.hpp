#pragma once

#include <sstream>
#include <string>

struct SHR {
  int target_register;

  std::string str() const {
    std::stringstream ss;
    ss << "SHR[" << target_register << "]";
    return ss.str();
  }
};
