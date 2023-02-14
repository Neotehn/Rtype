#ifndef ECS_DATATYPESECS_HPP_
#define ECS_DATATYPESECS_HPP_

#include <iostream>
#include <string>
#include <vector>
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
};

struct SystemData {
  EventQueue event_queue;
};

struct Pos {
  sf::Vector2f velocity;
  sf::Vector2f position;
};

class HealthBar {
 public:
  HealthBar(std::vector<std::string> t_sprites_paths, int t_health) {
    m_sprites_paths = t_sprites_paths;
    m_health = t_health;
  }

  const int getHealth() { return m_health; }
  const std::vector<std::string> getSpritesPaths() { return m_sprites_paths; }
  void setHealth(int t_health) { m_health = t_health; }

 private:
  int m_health;
  std::vector<std::string> m_sprites_paths;
};

struct Health {
  HealthBar healthbar;
  Pos position;
  sf::RectangleShape body;
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

struct BackgroundLayer {
  SpriteECS sprite;
  sf::Vector2f position;
  float speed;
  int limit;
};

struct Player {
  SpriteECS sprite;
  Pos position;
  sf::RectangleShape body;
  Health health;
  float speed;
};

struct Bullet {
  sf::RectangleShape body;
  float speed;
  sf::Vector2f pos;
};

struct AnimationObj {
  std::string type;
  Pos position;
  AnimationTime time;
  AnimationRect rect;
  sf::RectangleShape body;
};

#endif  // ECS_DATATYPESECS_HPP_
