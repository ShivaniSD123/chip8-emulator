#pragma once

#include <sstream>
#include <string>

struct SET_SOUND_TIMER {
  int target_register;

  std::string str() const {
    std::stringstream ss;
    ss << "SET_SOUND_TIMER[" << target_register << "]";
    return ss.str();
  }
};
