#ifndef R_TYPE_CLIENT_PLAYER_H
#define R_TYPE_CLIENT_PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Player {
 private:
  sf::Sprite _sprite;
  sf::Texture _texture;
  sf::RectangleShape _body;
  float _speed;
  sf::Vector2f _velocity;
  sf::Vector2f _position;
  float _angle;

 public:
  Player(std::string sprite_path);
  bool loadFromFile(std::string filepath);
  void display(sf::RenderWindow &window);
  void setPosition(float x, float y);
  void handlePlayerInput(sf::Event &event);
  void move(sf::Vector2f direction);
  void update(sf::Vector2f windowSize);
  sf::Vector2f getPosition() { return _position; }
};

#endif  // R_TYPE_CLIENT_PLAYER_H
