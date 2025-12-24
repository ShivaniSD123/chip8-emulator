#pragma once

#include <sstream>
#include <string>

struct JMP_ADDR {
  int addr;
  std::string str() const {
    std::stringstream ss;
    ss << "JMP_ADDR[" << addr << "]";
    return ss.str();
  }
};
