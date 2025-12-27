#pragma once

#include <sstream>
#include <string>

struct SET_DELAY_TIMER {
  int target;

  std::string str() const {
    std::stringstream ss;
    ss << "SET_DELAY_TIMER" << target << "]";
    return ss.str();
  }
};
