#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Sprite {
 public:
  Sprite(std::string path, sf::Vector2f pos);
  ~Sprite();
  sf::Sprite &getSprite() { return m_sprite; }
  void setPos(float pos_x = 0, float pos_y = 0) {
    m_sprite.setPosition(pos_x, pos_y);
  }
  sf::Texture &getTexture() { return m_texture; }
  void setPath(std::string path) { m_path = path; }
  std::string &getPath() { return m_path; }

 private:
  std::string m_path;
  sf::Texture m_texture;
  sf::Sprite m_sprite;
};

#endif  // !SPRITE_HPP_
