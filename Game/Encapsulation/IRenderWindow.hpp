#ifndef R_TYPE_CLIENT_IWINDOW_HPP
#define R_TYPE_CLIENT_IWINDOW_HPP

#include <string>

#include "Event.hpp"
#include "GraphicDataTypes.hpp"

namespace rtype {

  class IRenderWindow {
   public:
    ~IRenderWindow() = default;

    virtual void draw(sf::Sprite t_sprite) = 0;
    virtual void draw(sf::RectangleShape t_shape) = 0;
    virtual void display() = 0;
    virtual rtype::Vector2u getSize() const = 0;
    virtual bool isOpen() = 0;
    virtual void close() = 0;
    virtual void clear(rtype::Color t_color = {0, 0, 0, 255}) = 0;
    virtual void setFramerateLimit(unsigned int t_fps) = 0;
    virtual void create(unsigned int t_width, unsigned int t_height,
                        std::string t_title) = 0;
    virtual bool pollEvent(rtype::Event &t_event) = 0;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_IWINDOW_HPP
