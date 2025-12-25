#pragma once

#include <sstream>
#include <string>

struct SKP_REG_EQUALS {
  int first_register;
  int second_register;
  std::string str() const {
    std::stringstream ss;
    ss << "SKP_IF_REG_VAL_EQUALS[" << first_register << " " << second_register
       << "]";
    return ss.str();
  }
};
