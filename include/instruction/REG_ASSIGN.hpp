#pragma once

#include <sstream>
#include <string>

struct REG_ASSIGN {
  int to_register;
  int from_register;

  std::string str() const {
    std::stringstream ss;
    ss << "REG_ASSIGN[" << to_register << " " << from_register << "]";
    return ss.str();
  }
};
