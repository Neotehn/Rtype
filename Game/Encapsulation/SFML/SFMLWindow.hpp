#ifndef R_TYPE_CLIENT_SFML_WINDOW_HPP
#define R_TYPE_CLIENT_SFML_WINDOW_HPP

#include <string>

#include <SFML/Graphics.hpp>

#include "../IRenderWindow.hpp"

namespace rtype {

  class RenderWindow : public IRenderWindow {
   public:
    RenderWindow();
    RenderWindow(unsigned int t_width, unsigned int t_height,
                 std::string t_title);
    ~RenderWindow();

    void draw(sf::Sprite t_sprite) override;
    void draw(sf::RectangleShape t_shape) override;
    void display() override;
    rtype::Vector2u getSize() const override;
    bool isOpen() override;
    void close() override;
    void clear(rtype::Color t_color) override;
    void setFramerateLimit(unsigned int t_fps) override;
    void create(unsigned int t_width, unsigned int t_height,
                std::string t_title) override;
    bool pollEvent(rtype::Event &t_event) override;

   private:
    sf::RenderWindow m_window;
    sf::Event m_event;
    rtype::IRenderWindow *m_windowPtr;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_SFML_WINDOW_HPP
