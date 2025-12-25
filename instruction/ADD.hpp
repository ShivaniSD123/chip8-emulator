#pragma once

#include <sstream>
#include <string>

struct ADD {
  int first_register;
  int second_register;
  std::string str() const {
    std::stringstream ss;
    ss << "ADD[" << first_register << " " << second_register << "]";
    return ss.str();
  }
};
