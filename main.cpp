#include <fstream>
#include <iostream>

#include "interpreter.hpp"

Program parseROM(std::string const filename) {
  std::vector<uint8_t> bytes;
  std::ifstream f(filename, std::ios::in | std::ios::binary);
  while (true) {
    uint8_t byte;
    if (!f.read(reinterpret_cast<char*>(&byte), 1)) break;
    bytes.push_back(byte);
  }
  return {bytes};
}

int main(int argc, char* argv[]) {
  using namespace std;
  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " <filename>\n";
    return 1;
  }

  string filename = argv[1];

  auto program = parseROM(filename);
  Interpreter vm(std::move(program));
  while (vm.is_running() == true) {
    vm.step();
  }
  return 0;
}
