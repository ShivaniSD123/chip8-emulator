#pragma once

#include <sstream>
#include <string>

struct SUB {
  int first_register;
  int second_register;
  std::string str() const {
    std::stringstream ss;
    ss << "SUB[" << first_register << " " << second_register << "]";
    return ss.str();
  }
};
