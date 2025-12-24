#pragma once

#include <sstream>
#include <string>

struct IND_ASSIGN {
  int ind_addr;
  std::string str() const {
    std::stringstream ss;
    ss << "IND_REG_ASSIGN[" << ind_addr << "]";
    return ss.str();
  }
};
