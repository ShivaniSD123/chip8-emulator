#pragma once

#include <sstream>
#include <string>

struct CALL_SUB {
  int addr;
  std::string str() const {
    std::stringstream ss;
    ss << "CALL_SUB[" << addr << "]";
    return ss.str();
  }
};
