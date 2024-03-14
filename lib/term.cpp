#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>

#include <term.hpp>

namespace term {
  const char* csi = "\e[";
  struct termios origMode;
  std::pair<int, int> getSize() {
    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    return std::pair(ws.ws_col, ws.ws_row);
  }
  void setRaw(bool enabled) {
    if(enabled) {
      struct termios mode;
      tcgetattr(STDIN_FILENO, &mode);
      origMode = mode;
      mode.c_lflag &= ~(ECHO | ICANON);
      tcsetattr(STDIN_FILENO, TCSAFLUSH, &mode);
    } else {
      tcsetattr(STDIN_FILENO, TCSAFLUSH, &origMode);
    }
  }
  void setAltBuf(bool enabled) {
    std::cout << csi << "?1049" << (enabled ? 'h' : 'l');
  }
  namespace cursor {
    void setPos(int x, int y) {
      std::cout << csi << y << ";" << x << "H";
    }
    void save() {
      std::cout << "\e7";
    }
    void restore() {
      std::cout << "\e8";
    }
    void left(int cols) {
      std::cout << csi << cols << 'D';
    }
    void down(int lines) {
      std::cout << csi << lines << 'B';
    }
    void up(int lines) {
      std::cout << csi << lines << 'A';
    }
    void right(int cols) {
      std::cout << csi << cols << 'C';
    }
    void setStyle(style newStyle) {
      std::cout << csi << newStyle << " q";
    }
  }
  void eraseInLine(selection mode) {
    std::cout << csi << mode << 'K';
  }
  void eraseInScreen(selection mode) {
    std::cout << csi << mode << 'J';
  }
  namespace graphic {
    namespace bg {
      void setCol(int r, int g, int b) {
        std::cout << csi << "48;2;" << r << ';' << g << ';' << b << 'm';
      }
    }
  }
}
