#ifndef R_TYPE_CLIENT_RAYLIBSPRITE_HPP
#define R_TYPE_CLIENT_RAYLIBSPRITE_HPP

#include <raylib.h>

#include "../ISprite.hpp"
#include "./RaylibTexture.hpp"

namespace rtype {
  class RaylibSprite : public ISprite {
   public:
    RaylibSprite();
    ~RaylibSprite();

    void setTexture(ITexture *texture, bool reset_rect) override;
    void setTextureRect(const IntRect &rectangle) override;
    void setPosition(const Vector2f &position) override;
    void setScale(const Vector2f &scale) override;
    void setRotation(float angle) override;
    void setOrigin(const Vector2f &origin) override;
    void setColor(const Color &color) override;

    void move(const Vector2f &offset) override;
    void scale(const Vector2f &factor) override;
    void rotate(float angle) override;

    rtype::Vector2u getSize() const override;
    const rtype::ITexture *getTexture() const override;
    rtype::FloatRect getLocalBounds() const override;
    rtype::FloatRect getGlobalBounds() const override;

    bool contains(const rtype::Vector2f &point) const override;

    IntRect getTextureRect();
    float getRotation();
    Vector2f getOrigin();
    Vector2f getPosition();
    Vector2f getScale();
    rtype::Color getColor();

   private:
    RaylibTexture *m_texture;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_RAYLIBSPRITE_HPP
