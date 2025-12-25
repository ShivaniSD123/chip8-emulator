#pragma once

#include <sstream>
#include <string>

struct JMP_ADDR {
  int address;
  std::string str() const {
    std::stringstream ss;
    ss << "JMP_ADDR[" << address << "]";
    return ss.str();
  }
};
