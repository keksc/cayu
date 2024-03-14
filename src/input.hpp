#pragma once

#include <vector>

#include "mode.hpp"
#include "buf.hpp"
#include "returnCode.hpp"

returnCode processInput(const char input, mode &currentMode, std::vector<Buf> &bufs);
