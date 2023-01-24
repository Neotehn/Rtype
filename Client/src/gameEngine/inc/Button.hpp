/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Button {
 public:
  Button(std::string path, float pos_x = 0, float pos_y = 0);
  sf::Sprite &getSprite() { return m_sprite; }
  void setPos(float pos_x = 0, float pos_y = 0) {
    m_sprite.setPosition(pos_x, pos_y);
  }
  void setPath(std::string path) { m_path = path; }
  std::string &getPath() { return m_path; }
  bool is_pressed(sf::Vector2f mouse_pos);
  bool is_hovered(sf::Vector2f mouse_pos);

 private:
  std::string m_path;
  sf::Texture m_texture;
  sf::Sprite m_sprite;
};

#endif /* !BUTTON_HPP_ */
