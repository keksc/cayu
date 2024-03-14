#include <iostream>

#include "print.hpp"
#include "term.hpp"

void printLine(std::string msg, int y) {
  term::cursor::save();
  term::cursor::setPos(1, y);
  term::eraseInLine(term::selection::full);
  std::cout << msg;
  term::cursor::restore();
}

void clearLine(int y) {
  term::cursor::save();
  term::cursor::setPos(1, y);
  term::eraseInLine(term::selection::full);
  term::cursor::restore();
}
