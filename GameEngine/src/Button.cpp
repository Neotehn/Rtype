#include "../inc/Button.hpp"

Button::Button(std::string t_path, sf::Vector2f t_pos,
               sf::Vector2f t_target_size)
    : Sprite(t_path, t_pos) {
  float pos_x = t_target_size.x / getTexture().getSize().x;
  float pos_y = t_target_size.y / getTexture().getSize().y;
  getSprite().setScale(pos_x, pos_y);
}

bool Button::is_hovered(sf::Vector2f t_mouse_pos) {
  if (getSprite().getGlobalBounds().contains(t_mouse_pos)) {
    getSprite().setColor(GRAY);
    return true;
  } else {
    getSprite().setColor(WHITE);
    return false;
  }
}

bool Button::is_pressed(sf::Vector2f t_mouse_pos) {
  if (getSprite().getGlobalBounds().contains(t_mouse_pos)) {
    getSprite().setColor(GRAY);
    return true;
  }
  getSprite().setColor(WHITE);
  return false;
}
