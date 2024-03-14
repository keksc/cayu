#include <iostream>

#include <term.hpp>

#include "input.hpp"

int main(int argc, char **argv) {
  term::setRaw(true);
  term::setAltBuf(true);
  term::graphic::bg::setCol(32, 32, 42);
  // term::eraseInLine(term::selection::full);
  std::cout << "\e[2J";
  mode currentMode;
  setMode(normal, currentMode);
  std::vector<Buf> bufs;
  for(int i=1;i<argc;i++) {
    bufs.push_back(Buf(argv[i]));
  }
  if(bufs.empty()) bufs.push_back(Buf()); else bufs[0].read();
  bufs[0].flush();
  while(true) {
    if(processInput(std::cin.get(), currentMode, bufs) == quit) break;
  }
  term::setAltBuf(false);
  term::setRaw(false);
}
