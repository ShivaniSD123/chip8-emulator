#pragma once

#include <iomanip>
#include <sstream>
#include <string>

struct CALL_SUB {
  int address;

  std::string str() const {
    std::stringstream ss;
    ss << "CALL_SUB[0x" << std::hex << std::setw(4) << std::setfill('0')
       << address << "]";
    return ss.str();
  }
};
