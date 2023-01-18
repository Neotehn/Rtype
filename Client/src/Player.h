#ifndef R_TYPE_CLIENT_PLAYER_H
#define R_TYPE_CLIENT_PLAYER_H

#include <iostream>
#include <SFML/Graphics.hpp>


class Player {
 private:
  sf::Sprite _sprite;
  sf::Texture _texture;
  sf::RectangleShape _body;
 public:
  // constructor to load the sprite
  Player(std::string sprite_path);
  bool loadFromFile(std::string filepath);
  void display(sf::RenderWindow &window);
  void setPosition(float x, float y);


};


#endif  // R_TYPE_CLIENT_PLAYER_H
