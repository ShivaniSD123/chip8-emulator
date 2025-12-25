#pragma once

#include <sstream>
#include <string>

struct OR {
  int first_register;
  int second_register;
  std::string str() const {
    std::stringstream ss;
    ss << "OR[" << first_register << " " << second_register << "]";
    return ss.str();
  }
};
