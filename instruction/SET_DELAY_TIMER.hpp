#pragma once

#include <sstream>
#include <string>

struct SET_DELAY_TIMER {
  int reg_addr;
  std::string str() const {
    std::stringstream ss;
    ss << "SET_DELAY_TIMER" << reg_addr << "]";
    return ss.str();
  }
};
