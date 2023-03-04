#ifndef R_TYPE_CLIENT_SPRITE_HPP
#define R_TYPE_CLIENT_SPRITE_HPP

#include "../ISprite.hpp"

#include <SFML/Graphics.hpp>

#include "./Texture.hpp"

namespace rtype {
  class Sprite : public ISprite {
   public:
    Sprite() = default;
    ~Sprite() override = default;

    void setTexture(rtype::ITexture *texture, bool reset_rect) override;
    void setTextureRect(const rtype::IntRect &rectangle) override;
    void setPosition(const rtype::Vector2f &position) override;
    void setScale(const rtype::Vector2f &factor) override;
    void setRotation(float angle) override;
    void setOrigin(const rtype::Vector2f &origin) override;
    void setColor(const rtype::Color &color) override;
    void move(const rtype::Vector2f &offset) override;
    void rotate(float angle) override;
    void scale(const rtype::Vector2f &factor) override;
    rtype::Vector2u getSize() const override;
    const rtype::ITexture *getTexture() const override;
    rtype::FloatRect getLocalBounds() const override;
    rtype::FloatRect getGlobalBounds() const override;

    bool contains(const rtype::Vector2f &point) const override;

    sf::Sprite &getSprite();

   private:
    sf::Sprite m_sprite;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_SPRITE_HPP
