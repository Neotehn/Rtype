#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <iostream>
#include <string>

#include "../../Game/Encapsulation/GraphicDataTypes.hpp"
#include "./Sprite.hpp"

#define GRAY                                                                   \
  rtype::Color { 128, 128, 128, 255 }

class Button : public Sprite {
 public:
  Button(std::string t_path, rtype::Vector2f t_pos,
         rtype::Vector2f t_target_size,
         rtype::IGraphicLoader *t_graphic_loader);
  bool is_pressed(rtype::Vector2f t_mouse_pos);
  bool is_hovered(rtype::Vector2f t_mouse_pos);
};

#endif  // !BUTTON_HPP_
