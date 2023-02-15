#ifndef R_TYPE_CLIENT_RECTANGLESHAPE_HPP
#define R_TYPE_CLIENT_RECTANGLESHAPE_HPP

#include <SFML/Graphics/RectangleShape.hpp>

namespace rtype {
  class RectangleShape {
   public:
    RectangleShape();
    ~RectangleShape();

    rtype::Vector2f getSize() const;
    void setSize(rtype::Vector2f t_size);
    void setPosition(rtype::Vector2f t_pos);
    void setFillColor(rtype::Color t_color);
    void setOutlineColor(rtype::Color t_color);
    void setOutlineThickness(float t_thickness);
    void draw(rtype::RenderWindow &t_window);
    void setTextureRect(rtype::IntRect t_rect);
    void setTexture(std::shared_ptr<sf::Texture> t_texture);
    rtype::FloatRect getGlobalBounds() const;

   private:
    sf::RectangleShape m_shape;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_RECTANGLESHAPE_HPP
