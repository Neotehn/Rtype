#include "Texture.hpp"

rtype::Texture::Texture() { m_texture = new sf::Texture(); }

rtype::Texture::Texture(const sf::Texture &texture) {
  m_texture = new sf::Texture(texture);
}

bool rtype::Texture::loadFromFile(const std::string &filename) {
  return m_texture->loadFromFile(filename);
}

bool rtype::Texture::loadFromFile(const std::string &filename,
                                  const IntRect &area) {
  sf::IntRect sfml_area(area.left, area.top, area.width, area.height);
  return m_texture->loadFromFile(filename, sfml_area);
}

rtype::Vector2u rtype::Texture::getSize() const {
  sf::Vector2u size = m_texture->getSize();
  return {size.x, size.y};
}

const sf::Texture *rtype::Texture::getTexture() { return m_texture; }
