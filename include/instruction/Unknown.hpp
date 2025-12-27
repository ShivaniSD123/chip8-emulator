#pragma once

#include <iomanip>
#include <sstream>
#include <string>

struct Unknown {
  uint16_t bits;

  std::string str() const {
    std::stringstream ss;
    ss << "Unknown[0x" << std::hex << std::setw(4) << std::setfill('0') << bits
       << "]";
    return ss.str();
  }
};
