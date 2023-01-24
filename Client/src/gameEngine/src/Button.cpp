/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** Button
*/

#include "../inc/Button.hpp"

Button::Button(std::string path, float pos_x, float pos_y) : m_path(path) {
  if (!m_texture.loadFromFile(m_path))
    std::cout << "Can't find image: " << m_path << std::endl;
  m_sprite.setTexture(m_texture);
  m_sprite.setPosition(pos_x, pos_y);
  m_sprite.setScale(0.3333333333, 0.333333333);
}

bool Button::is_hovered(sf::Vector2f mouse_pos) {
  if (m_sprite.getGlobalBounds().contains(mouse_pos)) {
    m_sprite.setColor(sf::Color(128, 128, 128));
    return true;
  } else {
    m_sprite.setColor(sf::Color(255, 255, 255));
    return false;
  }
}

bool Button::is_pressed(sf::Vector2f mouse_pos) {
  if (m_sprite.getGlobalBounds().contains(mouse_pos)) {
    m_sprite.setColor(sf::Color(128, 128, 128));
    return true;
  }
  m_sprite.setColor(sf::Color(255, 255, 255));
  return false;
}
