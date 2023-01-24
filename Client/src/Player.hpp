#ifndef CLIENT_SRC_PLAYER_HPP_
#define CLIENT_SRC_PLAYER_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>

class Player {
 public:
  Player(std::string sprite_path);
  bool loadFromFile(std::string t_filepath);
  void display(sf::RenderWindow &t_window);
  void setPosition(float t_x, float t_y);
  void handlePlayerInput(const sf::Event &t_event);
  void move(sf::Vector2f t_direction);
  void update(sf::Vector2f t_windowSize);
  sf::Vector2f getPosition() { return m_position; }

 private:
  sf::Sprite m_sprite;
  sf::Texture m_texture;
  sf::RectangleShape m_body;
  float m_speed;
  sf::Vector2f m_velocity;
  sf::Vector2f m_position;
  float m_angle;
};

#endif  // CLIENT_SRC_PLAYER_HPP_
