#pragma once

#include <utility>

namespace term {
  std::pair<int, int> getSize();
  void setRaw(bool enabled);
  void setAltBuf(bool enabled);
  namespace cursor {
    std::pair<int, int> getPos();
    void setPos(int x=1, int y=1);
    void save();
    void restore();
    void left(int cols = 1);
    void down(int lines = 1);
    void up(int line=1);
    void right(int cold=1);
    enum style {
      blockBlink = 0,
      block = 1,
      blockSteady = 2,
      underlineBlink = 3,
      underlineSteady = 4,
      barBlink = 5,
      barSteady = 6
    };
    void setStyle(style newStyle);
  }
  enum selection {
    cursor2End = 0,
    cursor2Begin = 1,
    full = 2
  };
  void eraseInLine(selection mode);
  void eraseInScreen(selection mode);
  namespace graphic {
    namespace bg {
      void setCol(int r, int g, int b);
      void reset();
    }
    namespace fg {
      void setCol(int r, int g, int b);
      void reset();
    }
    namespace intensity {
      void bold();
      void faint();
      void reset();
    }
  }
}
