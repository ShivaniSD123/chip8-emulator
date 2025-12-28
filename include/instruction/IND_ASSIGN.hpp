#pragma once

#include <iomanip>
#include <sstream>
#include <string>

struct IND_ASSIGN {
  int address;

  std::string str() const {
    std::stringstream ss;
    ss << "IND_ASSIGN[0x" << std::hex << std::setw(4) << std::setfill('0')
       << address << "]";
    return ss.str();
  }
};
