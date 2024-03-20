#include <string>
#include <vector>

#include "input.hpp"
#include "mode.hpp"
#include "print.hpp"
#include "returnCode.hpp"
#include <strUtils.hpp>
#include <term.hpp>

const int del = 127;

returnCode processNormal(const char input, mode &currentMode,
                         std::vector<Buf> &bufs) {
  switch (input) {
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
    printLine(std::to_string(term::cursor::getPos().first-3));
  }
  return ok;
}

std::string cmdBuf;
returnCode processCmd(const char input, mode &currentMode,
                      std::vector<Buf> &bufs) {
  switch (input) {
  case '\e':
    cmdBuf.clear();
    setMode(normal, currentMode);
    break;
  case '\n':
    if (cmdBuf == "q") {
      return quit;
    } else if (cmdBuf.substr(0, 1) == "e") {
      std::vector<std::string> tokens = strUtils::split(cmdBuf, ' ');
      bufs.push_back(bufs[0]);
      bufs[0] = tokens[1];
      // i=1 for not take the 'e' and the 1st arg as its alr processed
      // separately
      for (int i = 2; i < tokens.size(); i++) {
        bufs.push_back(Buf(tokens[i]));
      }
    } else if(cmdBuf == "w") {
      bufs[0].write();
    }
    cmdBuf.clear();
    setMode(normal, currentMode);
    break;
  case del:
    if (cmdBuf.empty())
      break;
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

returnCode processInsert(const char input, mode &currentMode,
                         std::vector<Buf> &bufs) {
  std::pair<int, int> cursorPos = term::cursor::getPos();
  auto& currentBufContent = bufs[0].getContent();
  switch (input) {
  case '\e':
    setMode(normal, currentMode);
    break;
  case del:
    {
    int line = cursorPos.second-2;
    int col = cursorPos.first-3;
    if(line == 0 && col == 0) break;
    if(currentBufContent[line].empty()) {
      currentBufContent.erase(currentBufContent.begin()+line);
      term::eraseInLine(term::selection::full);
      term::cursor::up();
      term::cursor::right(bufs[0].getContent()[line-1].size());
      break;
    }
    if(col == 0 && !bufs[0].getContent()[line].empty()) {
      term::cursor::up();
      term::cursor::right(bufs[0].getContent()[line-1].size());
      currentBufContent[line-1].append(currentBufContent[line]);
      currentBufContent.erase(currentBufContent.begin()+line);
      bufs[0].flush();
      break;
    }
    currentBufContent[line].erase(currentBufContent[line].begin()+cursorPos.first-4);
    term::cursor::left();
    bufs[0].flush();
    break;
  }
  default:
    int line = cursorPos.second-2;
    int col = cursorPos.first-3;
    currentBufContent[line].insert(currentBufContent[line].begin()+col, input);
    term::cursor::right();
    bufs[0].flush();
    printLine(std::to_string(line));
    break;
  }
  
  return ok;
}

returnCode processVisual(const char input, mode &currentMode,
                         std::vector<Buf> &bufs) {
  switch (input) {
  case '\e':
    setMode(normal, currentMode);
    break;
  }
  return ok;
}

returnCode processInput(const char input, mode &currentMode,
                        std::vector<Buf> &bufs) {
  switch (currentMode) {
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
