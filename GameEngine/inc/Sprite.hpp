#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class Sprite {
 public:
  Sprite(std::string t_path, sf::Vector2f t_pos);
  ~Sprite();
  sf::Sprite &getSprite() { return m_sprite; }
  void setPos(float t_pos_x = 0, float t_pos_y = 0) {
    m_sprite.setPosition(t_pos_x, t_pos_y);
  }
  sf::Texture &getTexture() { return m_texture; }
  void setPath(std::string t_path) { m_path = t_path; }
  std::string &getPath() { return m_path; }

 private:
  std::string m_path;
  sf::Texture m_texture;
  sf::Sprite m_sprite;
};

#endif  // !SPRITE_HPP_
