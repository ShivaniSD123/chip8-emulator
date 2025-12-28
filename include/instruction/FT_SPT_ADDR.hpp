#pragma once

#include <sstream>
#include <string>

struct FT_SPT_ADDR {
  int target_register;

  std::string str() const {
    std::stringstream ss;
    ss << "FT_SPT_ADDR[" << target_register << "]";
    return ss.str();
  }
};
