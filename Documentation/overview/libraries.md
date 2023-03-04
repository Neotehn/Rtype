# Libraries

To display our game we use [`SFML`](https://www.sfml-dev.org/) and for networking we use [`Boost.Asio`](https://www.boost.org/doc/libs/1\_81\_0/doc/html/boost\_asio.html).

In our project we encapsulated the SFML library. Therefore not every SFML classes is implemented. You will find our encapsulation in "./Game/Encapsulation/".

In order to implement a class you are missing first create an interface for that class in the "Encapsulation"-folder.

For better explanation I will show you the implementation with the Sprite class. As mentioned above we would create the "ISprite.hpp" interface.&#x20;

```
#ifndef R_TYPE_CLIENT_ISPRITE_HPP
#define R_TYPE_CLIENT_ISPRITE_HPP

#include <string>

#include "./GraphicDataTypes.hpp"
#include "./ITexture.hpp"

namespace rtype {
  class ISprite {
   public:
    virtual ~ISprite() = default;

    virtual void setTexture(rtype::ITexture *texture,
                            bool reset_rect = false) = 0;
    virtual void setTextureRect(const rtype::IntRect &rectangle) = 0;
    virtual void setPosition(const rtype::Vector2f &position) = 0;
    virtual void setScale(const rtype::Vector2f &factor) = 0;
    virtual void setRotation(float angle) = 0;
    virtual void setOrigin(const rtype::Vector2f &origin) = 0;
    virtual void setColor(const rtype::Color &color) = 0;
    virtual void move(const rtype::Vector2f &offset) = 0;
    virtual void rotate(float angle) = 0;
    virtual void scale(const rtype::Vector2f &factor) = 0;
    virtual const rtype::ITexture *getTexture() const = 0;
    virtual rtype::FloatRect getLocalBounds() const = 0;
    virtual rtype::FloatRect getGlobalBounds() const = 0;

    virtual bool contains(const rtype::Vector2f &point) const = 0;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_ISPRITE_HPP
```

We put it in a namespace to clarify that its our implementation.

For public functions we add all the function we need to use sprites in our game.

After that we move on to the "SFML"-subfolder. There we create two files "Sprite.hpp" and "Sprite.cpp".

Sprites.hpp:

```
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
```

Sprites.cpp:

```
#include "Sprite.hpp"

void rtype::Sprite::setTexture(rtype::ITexture *texture, bool reset_rect) {
  m_sprite.setTexture(*dynamic_cast<rtype::Texture *>(texture)->getTexture(),
                      reset_rect);
}

void rtype::Sprite::setTextureRect(const rtype::IntRect &rectangle) {
  sf::IntRect sfml_rectangle(rectangle.left, rectangle.top, rectangle.width,
                             rectangle.height);
  m_sprite.setTextureRect(sfml_rectangle);
}

void rtype::Sprite::setPosition(const rtype::Vector2f &position) {
  m_sprite.setPosition(position.x, position.y);
}

void rtype::Sprite::setScale(const rtype::Vector2f &factor) {
  m_sprite.setScale(factor.x, factor.y);
}

void rtype::Sprite::setRotation(float angle) { m_sprite.setRotation(angle); }

void rtype::Sprite::setOrigin(const rtype::Vector2f &origin) {
  m_sprite.setOrigin(origin.x, origin.y);
}

void rtype::Sprite::setColor(const rtype::Color &color) {
  sf::Color sfml_color(color.r, color.g, color.b, color.a);
  m_sprite.setColor(sfml_color);
}

void rtype::Sprite::move(const rtype::Vector2f &offset) {
  m_sprite.move(offset.x, offset.y);
}

void rtype::Sprite::rotate(float angle) { m_sprite.rotate(angle); }

void rtype::Sprite::scale(const rtype::Vector2f &factor) {
  m_sprite.scale(factor.x, factor.y);
}

const rtype::ITexture *rtype::Sprite::getTexture() const {
  const sf::Texture *sfml_texture = m_sprite.getTexture();
  rtype::Texture *texture = new rtype::Texture(*sfml_texture);
  return texture;
}

rtype::FloatRect rtype::Sprite::getLocalBounds() const {
  sf::FloatRect sfml_bounds = m_sprite.getLocalBounds();
  return rtype::FloatRect{sfml_bounds.left, sfml_bounds.top, sfml_bounds.width,
                          sfml_bounds.height};
}

rtype::FloatRect rtype::Sprite::getGlobalBounds() const {
  sf::FloatRect sfml_bounds = m_sprite.getGlobalBounds();
  return rtype::FloatRect{sfml_bounds.left, sfml_bounds.top, sfml_bounds.width,
                          sfml_bounds.height};
}

bool rtype::Sprite::contains(const rtype::Vector2f &point) const {
  return m_sprite.getGlobalBounds().contains(point.x, point.y);
}

sf::Sprite &rtype::Sprite::getSprite() { return m_sprite; }
```

[BACK](../)
