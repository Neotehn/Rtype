#include "RaylibFont.hpp"

rtype::RaylibFont::RaylibFont() {
  m_font = LoadFont("./assets/font/nasalization-rg.ttf");
}

rtype::RaylibFont::RaylibFont(const Font &font) { m_font = font; }

bool rtype::RaylibFont::loadFromFile(const std::string &filename) {
  LoadFont(filename.c_str());
  return true;
}

const Font rtype::RaylibFont::getFont() { return m_font; }
