#include "./Button.hpp"

Button::Button(std::string t_path, rtype::Vector2f t_pos,
               rtype::Vector2f t_target_size,
               rtype::IGraphicLoader *t_graphic_loader, bool t_is_white)
    : Sprite(t_path, {t_pos.x, t_pos.y}, t_graphic_loader),
      m_is_white(t_is_white) {
  float pos_x = t_target_size.x / getTexture()->getSize().x;
  float pos_y = t_target_size.y / getTexture()->getSize().y;
  getSprite()->setScale({pos_x, pos_y});
  if (m_is_white) {
    getSprite()->setColor(BLUE);
  } else {
    getSprite()->setColor(rtype::White);
  }
}

bool Button::is_hovered(rtype::Vector2f t_mouse_pos) {
  if (getSprite()->contains({t_mouse_pos.x, t_mouse_pos.y})) {
    getSprite()->setColor(GRAY);
    return true;
  } else {
    if (m_is_white) {
      getSprite()->setColor(BLUE);
    } else {
      getSprite()->setColor(rtype::White);
    }
    return false;
  }
}

bool Button::is_pressed(rtype::Vector2f t_mouse_pos) {
  if (getSprite()->contains({t_mouse_pos.x, t_mouse_pos.y})) {
    getSprite()->setColor(GRAY);
    return true;
  }
  if (m_is_white) {
    getSprite()->setColor(BLUE);
  } else {
    getSprite()->setColor(rtype::White);
  }
  return false;
}
