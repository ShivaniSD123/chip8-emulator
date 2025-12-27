#pragma once

#include <iostream>

[[noreturn]] void fatalError(const std::string& msg) {
  std::cerr << "PANIC: " << msg << std::endl;
  std::terminate();
}

void precondition(bool condition, std::string msg = "Assertion Failed!") {
  if (!condition) {
    fatalError(msg);
  }
}

// helper type for the visitor #4
template <class... Ts>
struct overloaded : Ts... {
  using Ts::operator()...;
};
// explicit deduction guide (not needed as of C++20)
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;