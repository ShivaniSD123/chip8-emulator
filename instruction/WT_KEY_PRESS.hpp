#pragma once

#include <sstream>
#include <string>

struct WT_KEY_PRESS {
  int reg_addr;
  std::string str() const {
    std::stringstream ss;
    ss << "WT_KEY_PRESS" << reg_addr << "]";
    return ss.str();
  }
};
