#pragma once

#include <sstream>
#include <string>

struct GET_DELAY_TIMER {
  int target;
  std::string str() const {
    std::stringstream ss;
    ss << "GET_DELAY_TIMER" << target << "]";
    return ss.str();
  }
};
