#pragma once

#include <sstream>
#include <string>

struct WT_KEY_PRESS {
  int target;
  std::string str() const {
    std::stringstream ss;
    ss << "WT_KEY_PRESS" << target << "]";
    return ss.str();
  }
};
