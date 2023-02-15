#ifndef R_TYPE_CLIENT_RECTANGLESHAPE_HPP
#define R_TYPE_CLIENT_RECTANGLESHAPE_HPP

#include <SFML/Graphics/RectangleShape.hpp>

#include "../IRectangleShape.hpp"

namespace rtype {
  class RectangleShape : public IRectangleShape {
   public:
    RectangleShape() = default;
    ~RectangleShape() = default;

    void setFillColor(const rtype::Color &color) override;
    void setOutlineColor(const rtype::Color &color) override;
    void setOutlineThickness(float thickness) override;

    void setSize(const rtype::Vector2f &size) override;
    void setPosition(const rtype::Vector2f &position) override;
    void setTexture(const sf::Texture &texture) override;
    void setTextureRect(const rtype::IntRect &rect) override;
    void setRotation(float angle) override;
    void setScale(const rtype::Vector2f &factors) override;
    void setOrigin(const rtype::Vector2f &origin) override;
    void rotate(float angle) override;
    void scale(const rtype::Vector2f &factors) override;

    const rtype::Vector2f &getSize() override;
    const rtype::Vector2f &getPosition() override;
    const rtype::FloatRect &getGlobalBounds() override;
    float getRotation() const override;
    const rtype::Vector2f &getScale() override;
    const rtype::Vector2f &getOrigin() override;

   private:
    sf::RectangleShape m_shape;
    rtype::Vector2f m_size;
    rtype::Vector2f m_position;
    rtype::Vector2f m_scale;
    rtype::Vector2f m_origin;
    rtype::FloatRect m_globalBounds;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_RECTANGLESHAPE_HPP
