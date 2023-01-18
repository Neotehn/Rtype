#include "Player.h"
Player::Player(std::string sprite_path) {
  loadFromFile(sprite_path);
  setPosition(100, 100);
  x_pos = 300;
  y_pos = 200;
  _body.setSize({100, 100});
  _body.setOrigin(_body.getSize().x / 2, _body.getSize().y / 2);
  _body.setPosition(x_pos, y_pos);
  _body.setTexture(&_texture);
  _speed = 10;
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

void Player::display(sf::RenderWindow &window) {
  ;
  window.draw(_body);
}

void Player::setPosition(float x, float y) { _sprite.setPosition(x, y); }

void Player::moveUp() {
  if (y_pos > _speed) y_pos -= _speed;
  // std::cout << "Fly up in function" << std::endl;
  // std::cout << y_pos << std::endl;
}

void Player::moveDown() {
  if (y_pos < 1550) y_pos += _speed;
  // std::cout << "Fly down in function" << std::endl;
  // std::cout << y_pos << std::endl;
}

void Player::accelerate() {
  if (x_pos < 600) x_pos += _speed;
  // std::cout << "accelerate in function" << std::endl;
  // std::cout << x_pos << std::endl;
}

void Player::decelerate() {
  if (x_pos > 50) x_pos -= _speed;
  // std::cout << "decelerate in switch" << std::endl;
  // std::cout << x_pos << std::endl;
}

void Player::handlePlayerInput(sf::Event &event) {
  switch (event.key.code) {
    case sf::Keyboard::W:
      moveUp();
      // std::cout << "Fly up in switch" << std::endl;
      // std::cout << y_pos << std::endl;
      setPosition(x_pos, y_pos);
      _body.setPosition(x_pos, y_pos);
      break;
    case sf::Keyboard::S:
      moveDown();
      // std::cout << "Fly down in switch" << std::endl;
      // std::cout << y_pos << std::endl;
      setPosition(x_pos, y_pos);
      _body.setPosition(x_pos, y_pos);
      break;
    case sf::Keyboard::D:
      accelerate();
      // std::cout << "accelerate in switch" << std::endl;
      // std::cout << x_pos << std::endl;
      setPosition(x_pos, y_pos);
      _body.setPosition(x_pos, y_pos);
      break;
    case sf::Keyboard::A:
      decelerate();
      // std::cout << "decelerate in switch" << std::endl;
      // std::cout << x_pos << std::endl;
      setPosition(x_pos, y_pos);
      _body.setPosition(x_pos, y_pos);
      break;
    default:
      break;
  }
}