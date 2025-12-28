#pragma once

#include <sstream>
#include <string>

struct SKP_KEY_NOT_PRESS {
  int target_register;

  std::string str() const {
    std::stringstream ss;
    ss << "SKP_KEY_NOT_PRESS[" << target_register << "]";
    return ss.str();
  }
};
