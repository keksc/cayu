#include <iostream>
#include <fstream>

#include "buf.hpp"
#include "term.hpp"

Buf::Buf(std::string filename) : m_filename(filename) {

}

void Buf::flush() {
  term::cursor::setPos();
  std::cout << m_content;
}

bool Buf::fileExists() {
  return true;
}

void Buf::read() {
  m_content.clear();
  std::ifstream ifile(m_filename);
  std::string line;
  while(std::getline(ifile, line)) {
    m_content += line + '\n';
  }
  m_content.pop_back(); // the extra \n
}

void Buf::write() {
  std::ofstream ofile(m_filename);
  ofile << m_content;
}

std::string Buf::getFilename() const {
  return m_filename;
}
