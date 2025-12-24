#pragma once

#include <sstream>
#include <string>

struct SKP_KEY_PRESS {
  int reg_addr;
  std::string str() const {
    std::stringstream ss;
    ss << "SKP_KEY_PRESS" << reg_addr << "]";
    return ss.str();
  }
};
