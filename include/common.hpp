#pragma once

#include <iostream>

[[noreturn]] void fatal_error(const std::string& msg) {
  std::cerr << "FATAL ERROR: " << msg << std::endl;
  std::terminate();
}

void precondition(bool condition,
                  const std::string& msg = "Assertion Failed!") {
  if (!condition) {
    fatal_error(msg);
  }
}

template <class... Ts>
struct overloaded : Ts... {
  using Ts::operator()...;
};