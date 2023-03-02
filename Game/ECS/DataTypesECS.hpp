#ifndef ECS_DATATYPESECS_HPP_
#define ECS_DATATYPESECS_HPP_

#include <iostream>
#include <string>
#include <vector>
#include "../Encapsulation/GraphicDataTypes.hpp"
#include "../Encapsulation/ITexture.hpp"
#include "../Encapsulation/ISprite.hpp"
#include "../Encapsulation/IRectangleShape.hpp"
#include "../Encapsulation/IGraphicLoader.hpp"
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
  rtype::Vector2f velocity;
  rtype::Vector2f position;
};

class HealthBar {
 public:
  HealthBar(std::vector<std::string> t_sprites_paths, int t_health) {
    m_sprites_paths = t_sprites_paths;
    m_health = t_health;
  }

  const int getHealth() { return m_health; }
  const std::vector<std::string> getSpritesPaths() { return m_sprites_paths; }
  void setHealth(int t_health) {
    if (t_health < 0 || t_health > m_max_health) return;
    m_health = t_health;
  }
  void increaseHealth(int t_health) {
    m_health += t_health;
    if (m_health > m_max_health) m_health = m_max_health;
  }
  void setMaxHealth(int t_max_health) { m_max_health = t_max_health; }

 private:
  int m_health;
  std::vector<std::string> m_sprites_paths;
  int m_max_health = 3;
};

struct Health {
  HealthBar healthbar;
  Pos position;
  rtype::IRectangleShape *body;
};

class SpriteECS {
 public:
  SpriteECS(std::string t_sprite_path, rtype::IGraphicLoader *t_graphic_loader,
            rtype::Vector2f t_scale = {1, 1},
            rtype::Color t_color = rtype::White) {
    m_sprite = t_graphic_loader->loadSprite();
    m_texture = t_graphic_loader->loadTexture();
    m_texture->loadFromFile(t_sprite_path);
    m_sprite->setTexture(m_texture);
    m_sprite->setScale({t_scale.x, t_scale.y});
    m_sprite->setColor(t_color);
  }

  const rtype::ISprite *getSprite() const { return m_sprite; }

  const rtype::ITexture *getTexture() const { return m_texture; }

  void setPosition(rtype::Vector2f pos) {
    m_sprite->setPosition({pos.x, pos.y});
  }

  bool loadFromFile(std::string t_filepath) {
    if (!m_texture->loadFromFile(t_filepath)) {
      std::cerr << "Error loading sprite" << std::endl;
      return false;
    }
    m_sprite->setTexture(m_texture);
    return true;
  }

 private:
  rtype::ISprite *m_sprite;
  rtype::ITexture *m_texture;
};

struct BackgroundLayer {
  SpriteECS sprite;
  rtype::Vector2f position;
  float speed;
  int limit;
};

struct Player {
  SpriteECS sprite;
  Pos position;
  rtype::IRectangleShape *body;
  Health health;
  float speed;
  int player_id;
  int fire_shot = 0;
  int bomb_shot = 0;
  int coin_shot = 0;
  int coins = 0;
  int exp = 0;
  int kills = 0;
  float damage_factor = 1;
};

struct Bullet {
  rtype::IRectangleShape *body;
  float speed;
  rtype::Vector2f pos;
  EntityID owner = 0;
  float damage = 1;
};

struct AnimationObj {
  std::string type;
  Pos position;
  AnimationTime time;
  AnimationRect rect;
  rtype::IRectangleShape *body;
  int kill_value = 5;
};

struct DynamicHealthBar {
  rtype::IRectangleShape *missing_health;
  rtype::IRectangleShape *left_health;
  int cur_health;
  int max_health;
  Pos position;
  rtype::Vector2f offset;
};

struct Enemy {
  AnimationObj *obj;
  DynamicHealthBar health;
};

namespace rtype {
  enum ItemType {
    NO_ITEM,  // needs to stay at first position in enum
    LIFE_ITEM,
    SPEED_ITEM,
    BOMB_ITEM,
    FIRE_ITEM,
  };
}

struct SpinningItem {
  rtype::ItemType type;
  int value;
  SpriteECS sprite;
  Pos position;
  AnimationTime time;
  rtype::IRectangleShape *body;
};

#endif  // ECS_DATATYPESECS_HPP_
