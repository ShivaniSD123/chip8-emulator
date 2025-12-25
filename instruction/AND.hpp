#pragma once

#include <sstream>
#include <string>

struct AND {
  int first_register;
  int second_register;
  std::string str() const {
    std::stringstream ss;
    ss << "AND[" << first_register << " " << second_register << "]";
    return ss.str();
  }
};
