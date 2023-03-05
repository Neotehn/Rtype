#ifndef R_TYPE_CLIENT_IWINDOW_HPP
#define R_TYPE_CLIENT_IWINDOW_HPP

#include <string>

#include "Event.hpp"
#include "GraphicDataTypes.hpp"
#include "IRectangleShape.hpp"
#include "ISprite.hpp"
#include "IText.hpp"

namespace rtype {
  class IRenderWindow {
   public:
    ~IRenderWindow() = default;

    virtual void draw(const rtype::ISprite *t_sprite) = 0;
    virtual void draw(rtype::IRectangleShape *t_shape) = 0;
    virtual void draw(const rtype::IText *t_text) = 0;
    virtual void display() = 0;
    virtual rtype::Vector2u getSize() const = 0;
    virtual bool isOpen() = 0;
    virtual void close() = 0;
    virtual void clear(rtype::Color t_color = {0, 0, 0, 255}) = 0;
    virtual void setFramerateLimit(unsigned int t_fps) = 0;
    virtual void create(unsigned int t_width, unsigned int t_height,
                        std::string t_title) = 0;
    virtual void create(unsigned int t_width, unsigned int t_height,
                        std::string t_title, rtype::Style t_style) = 0;
    virtual bool pollEvent(rtype::Event &t_event, rtype::Vector2i t_mouse_pos,
                           bool first = true) = 0;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_IWINDOW_HPP
