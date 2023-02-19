#ifndef R_TYPE_CLIENT_ISPRITE_HPP
#define R_TYPE_CLIENT_ISPRITE_HPP

#include <string>

#include "./GraphicDataTypes.hpp"
#include "./ITexture.hpp"

namespace rtype {
  class ISprite {
   public:
    virtual ~ISprite() = default;

    virtual void setTexture(rtype::ITexture *texture) = 0;
    virtual void setTextureRect(const rtype::IntRect &rectangle) = 0;
    virtual void setPosition(const rtype::Vector2f &position) = 0;
    virtual void setScale(const rtype::Vector2f &factor) = 0;
    virtual void setRotation(float angle) = 0;
    virtual void setOrigin(const rtype::Vector2f &origin) = 0;
    virtual void move(const rtype::Vector2f &offset) = 0;
    virtual void rotate(float angle) = 0;
    virtual void scale(const rtype::Vector2f &factor) = 0;
    virtual const rtype::ITexture *getTexture() const = 0;
    virtual rtype::FloatRect getLocalBounds() const = 0;
    virtual rtype::FloatRect getGlobalBounds() const = 0;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_ISPRITE_HPP
