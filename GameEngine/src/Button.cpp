#include "../inc/Button.hpp"

Button::Button(std::string path, sf::Vector2f pos, sf::Vector2f target_size)
    : Sprite(path, pos) {
  float pos_x = target_size.x / getTexture().getSize().x;
  float pos_y = target_size.y / getTexture().getSize().y;
  getSprite().setScale(pos_x, pos_y);
}

bool Button::is_hovered(sf::Vector2f mouse_pos) {
  if (getSprite().getGlobalBounds().contains(mouse_pos)) {
    getSprite().setColor(sf::Color(128, 128, 128));
    return true;
  } else {
    getSprite().setColor(sf::Color(255, 255, 255));
    return false;
  }
}

bool Button::is_pressed(sf::Vector2f mouse_pos) {
  if (getSprite().getGlobalBounds().contains(mouse_pos)) {
    getSprite().setColor(sf::Color(128, 128, 128));
    return true;
  }
  getSprite().setColor(sf::Color(255, 255, 255));
  return false;
}
