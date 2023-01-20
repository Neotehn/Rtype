#include "Player.hpp"

Player::Player(std::string sprite_path) {
  loadFromFile(sprite_path);
  _body.setSize({100, 100});
  _position = {300, 300};
  _body.setOrigin(_body.getSize().x / 2, _body.getSize().y / 2);
  setPosition(_position.x, _position.y);
  _body.setTexture(&_texture);
  _speed = 10;
  _velocity = sf::Vector2f(0, 0);
  _angle = 90.0f;
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

void Player::display(sf::RenderWindow &window) { window.draw(_body); }

void Player::setPosition(float x, float y) {
  _sprite.setPosition(x, y);
  _body.setPosition(x, y);
}
void Player::move(sf::Vector2f direction) {
  _velocity = direction * _speed;
  _body.setRotation(_angle);
}

void Player::handlePlayerInput(sf::Event &event) {
  switch (event.key.code) {
    case sf::Keyboard::W:
      move(sf::Vector2f(0, -1));
      break;
    case sf::Keyboard::S:
      move(sf::Vector2f(0, 1));
      break;
    case sf::Keyboard::D:
      move(sf::Vector2f(1, 0));
      break;
    case sf::Keyboard::A:
      move(sf::Vector2f(-1, 0));
      break;
  }
}

void Player::update(sf::Vector2f windowSize) {
  if (_position.x <= _body.getSize().x / 2) {
    _velocity.x = 1;
  } else if (_position.x + _body.getSize().x >=
             windowSize.x + _body.getSize().x / 2) {
    _velocity.x = -1;
  }
  if (_position.y <= _body.getSize().y / 2) {
    _velocity.y = 1;
  } else if (_position.y + _body.getSize().y >=
             windowSize.y + _body.getSize().y / 2) {
    _velocity.y = -1;
  }
  _position += _velocity;
  _body.setPosition(_position);
  if (_velocity.x != 0 || _velocity.y != 0) _velocity *= 0.99f;
}
