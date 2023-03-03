/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** Font
*/

#include "Font.hpp"

rtype::Font::Font() { m_font = new sf::Font(); }

rtype::Font::Font(const sf::Font &font) { m_font = new sf::Font(font); }

bool rtype::Font::loadFromFile(const std::string &filename) {
  return m_font->loadFromFile(filename);
}

const sf::Font *rtype::Font::getFont() { return m_font; }
