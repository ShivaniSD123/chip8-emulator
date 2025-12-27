#pragma once

#include <sstream>
#include <string>

struct SET_SOUND_TIMER {
  int target;

  std::string str() const {
    std::stringstream ss;
    ss << "SET_SOUND_TIMER" << target << "]";
    return ss.str();
  }
};
