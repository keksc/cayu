#pragma once

enum mode {
  normal,
  cmd,
  insert,
  visual
};

void setMode(mode newMode, mode &currentMode);
