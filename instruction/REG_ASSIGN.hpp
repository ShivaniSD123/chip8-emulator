#pragma once

#include <sstream>
#include <string>

struct REG_ASSIGN {
  int to;
  int from;
  std::string str() const {
    std::stringstream ss;
    ss << "REG_ASSIGN[" << to << " " << from << "]";
    return ss.str();
  }
};
