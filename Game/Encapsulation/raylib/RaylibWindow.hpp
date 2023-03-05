#ifndef R_TYPE_CLIENT_RAYLIBWINDOW_HPP
#define R_TYPE_CLIENT_RAYLIBWINDOW_HPP

#include <string>
#include <vector>

#include <raylib.h>

#include "../IRenderWindow.hpp"
#include "./RaylibText.hpp"
#include "./RaylibSprite.hpp"
#include "./RaylibRectangleShape.hpp"

namespace rtype {

  class RaylibWindow : public IRenderWindow {
   public:
    RaylibWindow();
    RaylibWindow(unsigned int t_width, unsigned int t_height,
                 std::string t_title);
    ~RaylibWindow();

    void draw(const rtype::ISprite *t_sprite) override;
    void draw(rtype::IRectangleShape *t_shape) override;
    void draw(const rtype::IText *t_text) override;
    void display() override;
    rtype::Vector2u getSize() const override;
    bool isOpen() override;
    void close() override;
    void clear(rtype::Color t_color) override;
    void setFramerateLimit(unsigned int t_fps) override;
    void create(unsigned int t_width, unsigned int t_height,
                std::string t_title) override;
    void create(unsigned int t_width, unsigned int t_height,
                std::string t_title, rtype::Style t_style) override;
    bool pollEvent(rtype::Event &t_event) override;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_RAYLIBWINDOW_HPP
