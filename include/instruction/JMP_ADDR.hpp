#pragma once

#include <iomanip>
#include <sstream>
#include <string>

struct JMP_ADDR {
  int address;

  std::string str() const {
    std::stringstream ss;
    ss << "JMP_ADDR[0x" << std::hex << std::setw(4) << std::setfill('0')
       << address << "]";
    return ss.str();
  }
};
