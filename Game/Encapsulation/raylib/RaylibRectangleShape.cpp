#include "RaylibRectangleShape.hpp"

namespace rtype {
  void RaylibRectangleShape::setFillColor(const rtype::Color &color) {
    m_texture->setColor(color);
  }

  void RaylibRectangleShape::setOutlineColor(const rtype::Color &color) {}

  void RaylibRectangleShape::setOutlineThickness(float thickness) {}

  void RaylibRectangleShape::setSize(const rtype::Vector2f &size) {
    m_texture->setSize(size);
  }

  void RaylibRectangleShape::setPosition(const rtype::Vector2f &position) {
    m_texture->setPosition(position);
  }

  void RaylibRectangleShape::setTexture(const rtype::ITexture *texture) {
    rtype::ITexture *tmp = const_cast<rtype::ITexture *>(texture);
    m_texture = dynamic_cast<RaylibTexture *>(tmp);
  }

  void RaylibRectangleShape::setTextureRect(const rtype::IntRect &rect) {
    Rectangle rect_tmp = {
      static_cast<float>(rect.left), static_cast<float>(rect.top),
      static_cast<float>(rect.width), static_cast<float>(rect.height)};
    m_texture->setRect(rect_tmp);
  }

  void RaylibRectangleShape::setRotation(float angle) {
    m_texture->setRotation(angle);
  }

  void RaylibRectangleShape::setScale(const rtype::Vector2f &factors) {
    m_texture->setScale(factors);
  }

  void RaylibRectangleShape::setOrigin(const rtype::Vector2f &origin) {
    m_texture->setOrigin(origin);
  }

  void RaylibRectangleShape::rotate(float angle) { m_texture->rotate(angle); }

  void RaylibRectangleShape::scale(const rtype::Vector2f &factors) {
    m_texture->scale(factors);
  }

  bool RaylibRectangleShape::intersects(const rtype::FloatRect &rect) {
    Rectangle rect_tmp = {
      static_cast<float>(rect.left), static_cast<float>(rect.top),
      static_cast<float>(rect.width), static_cast<float>(rect.height)};
    return CheckCollisionRecs(m_texture->getRect(), rect_tmp);
  }

  IRectangleShape::SIDE
  RaylibRectangleShape::intersectsSide(const rtype::FloatRect &rect) {
    FloatRect shape_rect = m_texture->getGlobalBounds();
    shape_rect.width += shape_rect.left;
    shape_rect.height += shape_rect.top;
    FloatRect obstacle_rect = FloatRect{
      rect.left, rect.top, rect.width + rect.left, rect.height + rect.top};
    rtype::IRectangleShape::SIDE side = rtype::IRectangleShape::SIDE::NONE;

    if (intersects(FloatRect{rect.left, rect.top, rect.width, rect.height})) {
      // left, top, right, bottom
      FloatRect intersection_rect = {
        std::min(shape_rect.left, obstacle_rect.left),
        std::min(shape_rect.top, obstacle_rect.top),
        std::max(shape_rect.width, obstacle_rect.width),
        std::max(shape_rect.height, obstacle_rect.height)};
      float width = intersection_rect.width - intersection_rect.left;
      float height = intersection_rect.height - intersection_rect.top;

      if (intersection_rect.left == shape_rect.left && height > width) {
        side = rtype::IRectangleShape::SIDE::LEFT;
      } else if (intersection_rect.top == shape_rect.top && width > height) {
        side = rtype::IRectangleShape::SIDE::TOP;
      } else if (intersection_rect.width == shape_rect.width &&
                 height > width) {
        side = rtype::IRectangleShape::SIDE::RIGHT;
      } else if (intersection_rect.height == shape_rect.height &&
                 width > height) {
        side = rtype::IRectangleShape::SIDE::BOTTOM;
      }
    };
    return side;
  }

  const rtype::Vector2f &RaylibRectangleShape::getSize() {
    rtype::Vector2u size = m_texture->getSize();
    return {static_cast<float>(size.x), static_cast<float>(size.y)};
  }

  const rtype::Vector2f &RaylibRectangleShape::getPosition() {
    return m_texture->getPosition();
  }

  const rtype::FloatRect &RaylibRectangleShape::getGlobalBounds() {
    return m_texture->getGlobalBounds();
  }

  const rtype::IntRect &RaylibRectangleShape::getTextureRect() {
    Rectangle rect = m_texture->getRect();
    return {static_cast<int>(rect.x), static_cast<int>(rect.y),
            static_cast<int>(rect.width), static_cast<int>(rect.height)};
  }

  float RaylibRectangleShape::getRotation() const {
    return m_texture->getRotation();
  }

  const rtype::Vector2f &RaylibRectangleShape::getScale() {
    return m_texture->getScale();
  }

  const rtype::Vector2f &RaylibRectangleShape::getOrigin() {
    return m_texture->getOrigin();
  }

  RaylibTexture *RaylibRectangleShape::getTexture() const { return m_texture; }
}  // namespace rtype
