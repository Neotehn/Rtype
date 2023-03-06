#ifndef R_TYPE_CLIENT_RAYLIBRECTANGLESHAPE_HPP
#define R_TYPE_CLIENT_RAYLIBRECTANGLESHAPE_HPP

#include <raylib.h>

#include "../IRectangleShape.hpp"
#include "./RaylibTexture.hpp"

namespace rtype {
  class RaylibRectangleShape : public IRectangleShape {
   public:
    RaylibRectangleShape() = default;
    ~RaylibRectangleShape() = default;

    void setFillColor(const rtype::Color &color) override;
    void setOutlineColor(const rtype::Color &color) override;
    void setOutlineThickness(float thickness) override;

    void setSize(const rtype::Vector2f &size) override;
    void setPosition(const rtype::Vector2f &position) override;
    void setTexture(const rtype::ITexture *texture) override;
    void setTextureRect(const rtype::IntRect &rect) override;
    void setRotation(float angle) override;
    void setScale(const rtype::Vector2f &factors) override;
    void setOrigin(const rtype::Vector2f &origin) override;
    void rotate(float angle) override;
    void scale(const rtype::Vector2f &factors) override;

    bool intersects(const rtype::FloatRect &rect) override;
    SIDE intersectsSide(const rtype::FloatRect &rect) override;

    const rtype::Vector2f &getSize() override;
    const rtype::Vector2f &getPosition() override;
    const rtype::FloatRect &getGlobalBounds() override;
    const rtype::IntRect &getTextureRect() override;
    float getRotation() const override;
    const rtype::Vector2f &getScale() override;
    const rtype::Vector2f &getOrigin() override;

    RaylibTexture *getTexture() const;

   private:
    RaylibTexture *m_texture;
    IntRect m_texture_rect;
    Vector2f m_size = {0, 0};
    FloatRect m_global_bounds = {0, 0, 0, 0};
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_RAYLIBRECTANGLESHAPE_HPP
