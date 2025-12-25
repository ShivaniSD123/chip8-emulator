#pragma once

#include <sstream>
#include <string>

struct DRW_SPRITE {
  int first_register;
  int second_register;
  int val;
  std::string str() const {
    std::stringstream ss;
    ss << "DRW_SPRITE[" << first_register << " " << second_register << " "
       << val << "]";
    return ss.str();
  }
};
