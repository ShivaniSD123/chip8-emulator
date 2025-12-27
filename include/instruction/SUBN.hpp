#pragma once

#include <sstream>
#include <string>

struct SUBN {
  int first_register;
  int second_register;

  std::string str() const {
    std::stringstream ss;
    ss << "SUBN[" << first_register << " " << second_register << "]";
    return ss.str();
  }
};
