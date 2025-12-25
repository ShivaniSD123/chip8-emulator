#pragma once

#include <sstream>
#include <string>

struct SKP_REG_NOT_EQUALS {
  int first_register;
  int second_register;
  std::string str() const {
    std::stringstream ss;
    ss << "SKP_REG_NOT_EQUALS[" << first_register << " " << second_register
       << "]";
    return ss.str();
  }
};
