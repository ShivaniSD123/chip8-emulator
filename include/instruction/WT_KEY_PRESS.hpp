#pragma once

#include <sstream>
#include <string>

struct WT_KEY_PRESS {
  int target_register;

  std::string str() const {
    std::stringstream ss;
    ss << "WT_KEY_PRESS[" << target_register << "]";
    return ss.str();
  }
};
