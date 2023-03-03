/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** Text
*/

#include "Text.hpp"

void rtype::Text::setFont(rtype::IFont *font) {
  m_text.setFont(*dynamic_cast<rtype::Font *>(font)->getFont());
}

void rtype::Text::setPosition(const rtype::Vector2f &position) {
  m_text.setPosition(position.x, position.y);
}

void rtype::Text::setString(const std::string &string) {
  m_text.setString(string);
}

void rtype::Text::setCharacterSize(unsigned int size) {
  m_text.setCharacterSize(size);
}

void rtype::Text::setColor(const rtype::Color &color) {
  sf::Color sfml_color(color.r, color.g, color.b, color.a);
  m_text.setColor(sfml_color);
}

const rtype::IFont *rtype::Text::getFont() const {
  const sf::Font *sfml_font = m_text.getFont();
  rtype::Font *font = new rtype::Font(*sfml_font);
  return font;
}

unsigned int rtype::Text::getCharacterSize() const {
  return m_text.getCharacterSize();
}

// const rtype::Color &rtype::Text::getColor() const {

// }

void rtype::Text::setScale(const rtype::Vector2f &factor) {
  sf::Vector2f sfml_vector(factor.x, factor.y);
  m_text.setScale(sfml_vector);
}

const rtype::Vector2f &rtype::Text::getPosition() const {
  const sf::Vector2f sfml_vector = m_text.getPosition();
  rtype::Vector2f vector{sfml_vector.x, sfml_vector.y};
  return vector;
}

const std::string &rtype::Text::getString() const { return m_text.getString(); }

rtype::FloatRect rtype::Text::getLocalBounds() const {
  sf::FloatRect sfml_bounds = m_text.getLocalBounds();
  return rtype::FloatRect{sfml_bounds.left, sfml_bounds.top, sfml_bounds.width,
                          sfml_bounds.height};
}

sf::Text &rtype::Text::getText() { return m_text; }