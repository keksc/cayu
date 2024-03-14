#pragma once

#include <string>

class Buf {
  std::string m_filename;
  std::string m_content;
public:
  Buf(std::string filename="");
  void flush();
  bool fileExists();
  void read();
  void write();
  std::string getFilename() const;
};
