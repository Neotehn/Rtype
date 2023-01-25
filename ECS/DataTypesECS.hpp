#ifndef ECS_DATATYPESECS_HPP_
#define ECS_DATATYPESECS_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Client/src/EventQueue.hpp"

struct SystemData {
  EventQueue event_queue;
};

struct Pos {
  sf::Vector2f velocity;
  sf::Vector2f position;
};

class SpriteECS {
 public:
  SpriteECS(std::string t_sprite_path) {
    m_texture->loadFromFile(t_sprite_path);
    m_sprite.setTexture(*m_texture);
  }

  const sf::Sprite* getSprite() const { return &m_sprite; }

  const sf::Texture* getTexture() const { return m_texture; }

  bool loadFromFile(std::string t_filepath) {
    if (!m_texture->loadFromFile(t_filepath)) {
      std::cerr << "Error loading sprite" << std::endl;
      return false;
    }
    m_sprite.setTexture(*m_texture);
    return true;
  }

 private:
  sf::Sprite m_sprite;
  sf::Texture* m_texture = new sf::Texture();

};

#endif  // ECS_DATATYPESECS_HPP_
