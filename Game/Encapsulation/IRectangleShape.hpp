#ifndef R_TYPE_CLIENT_IRECTANGLESHAPE_HPP
#define R_TYPE_CLIENT_IRECTANGLESHAPE_HPP

#include "./GraphicDataTypes.hpp"
#include "./ITexture.hpp"

namespace rtype {
  class IRectangleShape {
   public:
    virtual ~IRectangleShape() = default;

    virtual void setFillColor(const rtype::Color &) = 0;
    virtual void setOutlineColor(const rtype::Color &) = 0;
    virtual void setOutlineThickness(float) = 0;

    virtual void setSize(const rtype::Vector2f &) = 0;
    virtual void setPosition(const rtype::Vector2f &) = 0;
    virtual void setTexture(const rtype::ITexture *) = 0;
    virtual void setTextureRect(const rtype::IntRect &) = 0;
    virtual void setRotation(float) = 0;
    virtual void setScale(const rtype::Vector2f &) = 0;
    virtual void setOrigin(const rtype::Vector2f &) = 0;
    virtual void rotate(float) = 0;
    virtual void scale(const rtype::Vector2f &) = 0;

    virtual bool intersects(const rtype::FloatRect &) = 0;

    virtual const rtype::Vector2f &getSize() = 0;
    virtual const rtype::Vector2f &getPosition() = 0;
    virtual const rtype::FloatRect &getGlobalBounds() = 0;
    virtual const rtype::IntRect &getTextureRect() = 0;
    virtual float getRotation() const = 0;
    virtual const rtype::Vector2f &getScale() = 0;
    virtual const rtype::Vector2f &getOrigin() = 0;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_IRECTANGLESHAPE_HPP
