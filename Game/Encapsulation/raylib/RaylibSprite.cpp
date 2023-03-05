#include "RaylibSprite.hpp"

namespace rtype {
  RaylibSprite::RaylibSprite() {}

  RaylibSprite::~RaylibSprite() { delete m_texture; }

  void RaylibSprite::setTexture(ITexture *texture, bool reset_rect) {
    m_texture = dynamic_cast<RaylibTexture *>(texture);
  }

  void RaylibSprite::setTextureRect(const IntRect &rect) {
    m_texture->setRect(
      {static_cast<float>(rect.left), static_cast<float>(rect.top),
       static_cast<float>(rect.width), static_cast<float>(rect.height)});
  }

  void RaylibSprite::setPosition(const Vector2f &position) {
    m_texture->setPosition({position.x, position.y});
  }

  void RaylibSprite::setRotation(float angle) { m_texture->setRotation(angle); }

  void RaylibSprite::setScale(const Vector2f &scale) {
    m_texture->setScale({scale.x, scale.y});
  }

  void RaylibSprite::setOrigin(const Vector2f &origin) {
    m_texture->setOrigin({origin.x, origin.y});
  }

  void RaylibSprite::setColor(const Color &color) {
    m_texture->setColor({color.r, color.g, color.b, color.a});
  }

  void RaylibSprite::move(const Vector2f &offset) { m_texture->move(offset); }

  void RaylibSprite::rotate(float angle) { m_texture->rotate(angle); }

  void RaylibSprite::scale(const Vector2f &factor) { m_texture->scale(factor); }

  Vector2u RaylibSprite::getSize() const { return m_texture->getSize(); }

  const ITexture *RaylibSprite::getTexture() const { return m_texture; }

  FloatRect RaylibSprite::getLocalBounds() const {
    rtype::Vector2f position = m_texture->getPosition();
    return {position.x, position.y, static_cast<float>(m_texture->getSize().x),
            static_cast<float>(m_texture->getSize().y)};
  }

  FloatRect RaylibSprite::getGlobalBounds() const {
    rtype::Vector2f position = m_texture->getPosition();
    return {position.x, position.y, static_cast<float>(m_texture->getSize().x),
            static_cast<float>(m_texture->getSize().y)};
  }

  IntRect RaylibSprite::getTextureRect() {
    Rectangle rect = m_texture->getRect();
    return {static_cast<int>(rect.x), static_cast<int>(rect.y),
            static_cast<int>(rect.width), static_cast<int>(rect.height)};
  }

  bool RaylibSprite::contains(const rtype::Vector2f &point) const {
    if (point.x < m_texture->getPosition().x ||
        point.x > m_texture->getPosition().x + m_texture->getSize().x ||
        point.y < m_texture->getPosition().y ||
        point.y > m_texture->getPosition().y + m_texture->getSize().y)
      return false;
    return true;
  }

  Vector2f RaylibSprite::getPosition() { return m_texture->getPosition(); }

  Vector2f RaylibSprite::getScale() { return m_texture->getScale(); }

  Vector2f RaylibSprite::getOrigin() { return m_texture->getOrigin(); }

  rtype::Color RaylibSprite::getColor() { return m_texture->getColor(); }

  float RaylibSprite::getRotation() { return m_texture->getRotation(); }
}  // namespace rtype
