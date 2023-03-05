#include "RaylibTexture.hpp"

rtype::RaylibTexture::RaylibTexture() { m_texture = new Texture2D(); }

rtype::RaylibTexture::RaylibTexture(const Texture2D &texture) {
  m_texture = new Texture2D(texture);
}

bool rtype::RaylibTexture::loadFromFile(const std::string &filename) {
  *m_texture = LoadTexture(filename.c_str());
  return true;
}

bool rtype::RaylibTexture::loadFromFile(const std::string &filename,
                                        const IntRect &area) {
  *m_texture = LoadTexture(filename.c_str());
  return true;
}

rtype::Vector2u rtype::RaylibTexture::getSize() const {
  return {static_cast<unsigned int>(m_texture->width),
          static_cast<unsigned int>(m_texture->height)};
}

const Texture2D *rtype::RaylibTexture::getTexture() { return m_texture; }
const Rectangle &rtype::RaylibTexture::getRect() const { return m_rect; }
void rtype::RaylibTexture::setRect(const Rectangle &t_rect) { m_rect = t_rect; }
float rtype::RaylibTexture::getRotation() const { return m_rotation; }
void rtype::RaylibTexture::setRotation(float t_rotation) {
  m_rotation = t_rotation;
}
const rtype::Vector2f &rtype::RaylibTexture::getOrigin() const {
  return m_origin;
}
void rtype::RaylibTexture::setOrigin(const rtype::Vector2f &t_origin) {
  m_origin = t_origin;
}
const rtype::Vector2f &rtype::RaylibTexture::getPosition() const {
  return m_position;
}
void rtype::RaylibTexture::setPosition(const rtype::Vector2f &t_position) {
  m_position = t_position;
}
const rtype::Vector2f &rtype::RaylibTexture::getScale() const {
  return m_scale;
}
void rtype::RaylibTexture::setScale(const rtype::Vector2f &t_scale) {
  m_scale = t_scale;
}
const rtype::Color &rtype::RaylibTexture::getColor() const { return m_color; }
void rtype::RaylibTexture::setColor(const rtype::Color &t_color) {
  m_color = t_color;
}

void rtype::RaylibTexture::move(const rtype::Vector2f &offset) {
  m_position.x += offset.x;
  m_position.y += offset.y;
}

void rtype::RaylibTexture::rotate(float angle) { m_rotation += angle; }

void rtype::RaylibTexture::scale(const rtype::Vector2f &factor) {
  m_scale.x *= factor.x;
  m_scale.y *= factor.y;
}
void rtype::RaylibTexture::setSize(const rtype::Vector2f &t_size) {
  m_size = t_size;
}

rtype::FloatRect rtype::RaylibTexture::getGlobalBounds() const {
  return {m_position.x, m_position.y, m_size.x, m_size.y};
}

Texture *rtype::RaylibTexture::getTexture() const { return m_texture; }
