#ifndef R_TYPE_CLIENT_RENDERWINDOW_HPP
#define R_TYPE_CLIENT_RENDERWINDOW_HPP

#include <string>

#include <SFML/Graphics.hpp>

#include "../IRenderWindow.hpp"
#include "./Sprite.hpp"
#include "./RectangleShape.hpp"
#include "./Text.hpp"

namespace rtype {

  class RenderWindow : public IRenderWindow {
   public:
    RenderWindow();
    RenderWindow(unsigned int t_width, unsigned int t_height,
                 std::string t_title);
    ~RenderWindow();

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

    sf::RenderWindow *getRenderWindow();

   private:
    sf::RenderWindow m_window;
    sf::Event m_event;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_RENDERWINDOW_HPP
