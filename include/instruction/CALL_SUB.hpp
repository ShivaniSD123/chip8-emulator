#pragma once

#include <sstream>
#include <string>

struct CALL_SUB {
  int address;

  std::string str() const {
    std::stringstream ss;
    ss << "CALL_SUB[" << address << "]";
    return ss.str();
  }
};
