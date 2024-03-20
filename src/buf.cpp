#include <iostream>
#include <fstream>

#include "buf.hpp"
#include "term.hpp"

Buf::Buf(std::string filename) : m_filename(filename) {

}

void Buf::flush() {
  term::cursor::save();
  term::cursor::setPos(1, 2);
  for(int i=1;i<term::getSize().second-2;i++) {
    term::eraseInLine(term::selection::full);
    term::cursor::down();
  }
  term::cursor::setPos(1, 2);
  for(int i=0;i<m_content.size();i++) {
    term::eraseInLine(term::selection::full);
    term::graphic::fg::setCol(61, 61, 70);
    std::cout << i+1;
    term::graphic::fg::reset();
    std::cout << " " << m_content[i] << std::endl;
  }
  term::cursor::restore();
}

bool Buf::fileExists() {
  return true;
}

void Buf::read() {
  m_content.clear();
  std::ifstream ifile(m_filename);
  std::string line;
  while(std::getline(ifile, line)) {
    m_content.push_back(line);
  }
}

void Buf::write() {
  std::ofstream ofile(m_filename);
  for(auto& line : m_content) {
    ofile << line;
  }
}

std::string Buf::getFilename() const {
  return m_filename;
}

std::vector<std::string> &Buf::getContent() {
  return m_content;
}
