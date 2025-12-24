#pragma once

#include <sstream>
#include <string>

struct FT_SPT_ADDR {
  int reg_addr;
  std::string str() const {
    std::stringstream ss;
    ss << "FT_SPT_ADDR[" << reg_addr << "]";
    return ss.str();
  }
};
