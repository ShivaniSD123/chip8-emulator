#pragma once

#include <sstream>
#include <string>

struct GET_DELAY_TIMER {
  int reg_addr;
  std::string str() const {
    std::stringstream ss;
    ss << "GET_DELAY_TIMER" << reg_addr << "]";
    return ss.str();
  }
};
