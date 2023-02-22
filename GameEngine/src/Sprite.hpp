#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <iostream>
#include <string>

#include "../../Game/Encapsulation/GraphicDataTypes.hpp"
#include "../../Game/Encapsulation/ISprite.hpp"
#include "../../Game/Encapsulation/ITexture.hpp"
#include "../../Game/Encapsulation/IGraphicLoader.hpp"

class Sprite {
 public:
  Sprite(std::string t_path, rtype::Vector2f t_pos,
         rtype::IGraphicLoader *t_graphic_loader);
  ~Sprite();
  rtype::ISprite *getSprite();
  void setPos(float t_pos_x = 0, float t_pos_y = 0);
  rtype::ITexture *getTexture();
  void setPath(std::string t_path);
  std::string &getPath();

 private:
  std::string m_path;
  rtype::ITexture *m_texture;
  rtype::ISprite *m_sprite;
  rtype::IGraphicLoader *m_graphic_loader;
};

#endif  // !SPRITE_HPP_
