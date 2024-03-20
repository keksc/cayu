#pragma once

#include <string>
#include <vector>

class Buf {
  std::string m_filename;
  std::vector<std::string> m_content;
public:
  Buf(std::string filename="");
  void flush();
  bool fileExists();
  void read();
  void write();
  std::string getFilename() const;
  std::vector<std::string> &getContent();
};
