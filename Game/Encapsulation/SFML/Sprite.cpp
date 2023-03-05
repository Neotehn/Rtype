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

rtype::Vector2u rtype::Sprite::getSize() const {
  sf::Vector2u sfml_size = m_sprite.getTexture()->getSize();
  return rtype::Vector2u{sfml_size.x, sfml_size.y};
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
