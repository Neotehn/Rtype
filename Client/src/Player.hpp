#ifndef CLIENT_SRC_PLAYER_HPP_
#define CLIENT_SRC_PLAYER_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>

class Player {
 public:
  Player(std::string t_sprite_path);
  bool loadFromFile(std::string t_filepath);
  void display(sf::RenderWindow &t_window);
  void setPosition(float t_x, float t_y);
  void handlePlayerInput(const sf::Event &t_event);
  void move(sf::Vector2f t_direction);
  void update(sf::Vector2f t_window_size);
  sf::Vector2f getPosition() { return m_position; }

 private:
  sf::Sprite m_sprite;
  sf::Texture m_texture;
  sf::RectangleShape m_body;
  float m_speed = {10};
  sf::Vector2f m_velocity = {sf::Vector2f(0, 0)};
  sf::Vector2f m_position = {300, 300};
  float m_angle = {90};
};

#endif  // CLIENT_SRC_PLAYER_HPP_
