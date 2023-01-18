#include "Player.h"
Player::Player(std::string sprite_path) {
  loadFromFile(sprite_path);
  setPosition(100,100);
  _body.setSize({100, 100});
  _body.setOrigin(_body.getSize().x / 2, _body.getSize().y / 2);
  _body.setPosition(200, 200);
  _body.setTexture(&_texture);
}

bool Player::loadFromFile(std::string filepath) {
  sf::Image image;
  if (!_texture.loadFromFile(filepath)) {
    std::cerr << "Error loading sprite" << std::endl;
    return false;
  }
  _sprite.setTexture(_texture);
  return true;
}

void Player::display(sf::RenderWindow &window) {;
  window.draw(_body);
}

void Player::setPosition(float x, float y) {
  _sprite.setPosition(x, y);
}