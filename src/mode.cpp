#include <term.hpp>

#include "mode.hpp"
#include "print.hpp"

void setMode(mode newMode, mode &currentMode) {
  term::graphic::intensity::bold();
  term::graphic::bg::setCol(60, 60, 165);
  switch(newMode) {
    case normal:
      term::cursor::setStyle(term::cursor::style::blockBlink);
      printLine(" NORMAL", term::getSize().second-1);
      break;
    case cmd:
      printLine(" CMD", term::getSize().second-1);
      break;
    case insert:
      term::cursor::setStyle(term::cursor::style::barBlink);
      printLine(" INSERT", term::getSize().second-1);
      break;
    case visual:
      printLine(" VISUAL", term::getSize().second-1);
      break;
  }
  term::graphic::intensity::reset();
  term::graphic::bg::setCol(32, 32, 42);
  if(newMode == cmd) clearLine(term::getSize().second);
  currentMode = newMode;
}
