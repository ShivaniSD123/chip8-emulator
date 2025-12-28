#pragma once

#include <sstream>
#include <string>

struct DRW_SPRITE {
  int x_register;
  int y_register;
  int val;

  std::string str() const {
    std::stringstream ss;
    ss << "DRW_SPRITE[" << x_register << " " << y_register << " " << val << "]";
    return ss.str();
  }
};
