#pragma once

#include <sstream>
#include <string>

struct SET_SOUND_TIMER {
  int reg_addr;
  std::string str() const {
    std::stringstream ss;
    ss << "SET_SOUND_TIMER" << reg_addr << "]";
    return ss.str();
  }
};
