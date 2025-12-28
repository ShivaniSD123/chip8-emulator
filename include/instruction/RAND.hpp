
#pragma once

#include <iomanip>
#include <sstream>
#include <string>

struct RAND {
  int target_register;
  int mask;

  std::string str() const {
    std::stringstream ss;
    ss << "RAND[" << target_register << " " << mask << "]";
    return ss.str();
  }
};
