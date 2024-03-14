#include <iostream>
#include <vector>
#include <string>

#include <term.hpp>
#include <strUtils.hpp>
#include "input.hpp"
#include "mode.hpp"
#include "returnCode.hpp"
#include "print.hpp"

const int del = 127;

returnCode processNormal(const char input, mode &currentMode, std::vector<Buf> &bufs) {
  switch(input) {
    case ':':
      setMode(cmd, currentMode);
      break;
    case 'i':
      setMode(insert, currentMode);
      break;
    case 'v':
      setMode(visual, currentMode);
      break;
    case 'h':
      term::cursor::left();
      break;
    case 'j':
      term::cursor::down();
      break;
    case 'k':
      term::cursor::up();
      break;
    case 'l':
      term::cursor::right();
      break;
    case 'p':
      term::cursor::setStyle(term::cursor::style::barBlink);
      break;
  }
  return ok;
}

std::string cmdBuf;
returnCode processCmd(const char input, mode &currentMode, std::vector<Buf> &bufs) {
  switch(input) {
    case '\e':
      setMode(normal, currentMode);
      break;
    case '\n':
      if(cmdBuf == "q") {
        return quit;
      } else if(cmdBuf.substr(0, 1) == "e") {
        std::vector<std::string> tokens = strUtils::split(cmdBuf, ' ');
        Buf temp = bufs[0];
        bufs[0] = tokens[1];
        bufs.push_back(temp);
        // i=1 for not take the 'e' and the 1st arg as its alr processed separately 
        for(int i=2;i<tokens.size();i++) {
          bufs.push_back(Buf(tokens[i]));
          printLine(std::to_string(i), i);
        }
      }
      cmdBuf.clear();
      setMode(normal, currentMode);
      break;
    case del:
      if(cmdBuf.empty()) break;
      cmdBuf.pop_back();
      printLine(cmdBuf);
      break;
    default:
      cmdBuf.push_back(input);
      printLine(cmdBuf);
      break;
  }
  return ok;
}

returnCode processInsert(const char input, mode &currentMode, std::vector<Buf> &bufs) {
  switch(input) {
    case '\e':
      setMode(normal, currentMode);
      break;
  }
  return ok;
}

returnCode processVisual(const char input, mode &currentMode, std::vector<Buf> &bufs) {
  switch(input) {
    case '\e':
      setMode(normal, currentMode);
      break;
  }
  return ok;
}

returnCode processInput(const char input, mode &currentMode, std::vector<Buf> &bufs) {
  switch(currentMode) {
    case normal:
      return processNormal(input, currentMode, bufs);
      break;
    case cmd:
      return processCmd(input, currentMode, bufs);
      break;
    case insert:
      return processInsert(input, currentMode, bufs);
      break;
    case visual:
      return processVisual(input, currentMode, bufs);
      break;
  }
  return ok;
}
