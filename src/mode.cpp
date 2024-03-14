#include <term.hpp>

#include "mode.hpp"
#include "print.hpp"

void setMode(mode newMode, mode &currentMode) {
  switch(newMode) {
    case normal:
      term::cursor::setStyle(term::cursor::style::block);
      printLine("normal", term::getSize().second-1);
      break;
    case cmd:
      clearLine(term::getSize().second);
      printLine("cmd", term::getSize().second-1);
      break;
    case insert:
      term::cursor::setStyle(term::cursor::style::barBlink);
      printLine("insert", term::getSize().second-1);
      break;
    case visual:
      printLine("visual", term::getSize().second-1);
      break;
  }
  currentMode = newMode;
}
