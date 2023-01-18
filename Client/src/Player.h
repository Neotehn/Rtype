#ifndef R_TYPE_CLIENT_PLAYER_H
#define R_TYPE_CLIENT_PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Player {
 private:
  sf::Sprite _sprite;
  sf::Texture _texture;
  sf::RectangleShape _body;
  float x_pos;
  float y_pos;

 public:
  // constructor to load the sprite
  Player(std::string sprite_path);
  bool loadFromFile(std::string filepath);
  void display(sf::RenderWindow &window);
  void setPosition(float x, float y);
  void handlePlayerInput(sf::Event &event);
  void moveUp();
  void moveDown();
  void accelerate();
  void decelerate();
};

#endif  // R_TYPE_CLIENT_PLAYER_H
