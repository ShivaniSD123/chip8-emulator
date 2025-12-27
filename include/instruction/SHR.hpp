#pragma once

#include <sstream>
#include <string>

struct SHR {
  int first_register;
  int second_register;
  std::string str() const {
    std::stringstream ss;
    ss << "SHR[" << first_register << " " << second_register << "]";
    return ss.str();
  }
};
