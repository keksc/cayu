#pragma once

#include "term.hpp"
#include <string>

void printLine(std::string msg, int y=term::getSize().second);
void clearLine(int y);
