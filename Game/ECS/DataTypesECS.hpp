#ifndef ECS_DATATYPESECS_HPP_
#define ECS_DATATYPESECS_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../EventQueue.hpp"

struct AnimationTime {
  float current_animation_time;
  float display_time;
  float last_timer;
};

struct AnimationRect {
  int size;
  int limit;
  bool has_been_reset;
};

struct SystemData {
  EventQueue event_queue;
};

struct Pos {
  sf::Vector2f velocity;
  sf::Vector2f position;
};

class SpriteECS {
 public:
  SpriteECS(std::string t_sprite_path, sf::Vector2f t_scale = {1, 1}) {
    m_texture->loadFromFile(t_sprite_path);
    m_sprite.setTexture(*m_texture);
    m_sprite.setScale(t_scale);
  }

  const sf::Sprite *getSprite() const { return &m_sprite; }

  const sf::Texture *getTexture() const { return m_texture; }

  void setPosition(sf::Vector2f pos) { m_sprite.setPosition(pos); }

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
  sf::Texture *m_texture = new sf::Texture();
};

#endif  // ECS_DATATYPESECS_HPP_
