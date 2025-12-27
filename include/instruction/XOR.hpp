#pragma once

#include <sstream>
#include <string>

struct XOR {
  int first_register;
  int second_register;

  std::string str() const {
    std::stringstream ss;
    ss << "XOR[" << first_register << " " << second_register << "]";
    return ss.str();
  }
};
