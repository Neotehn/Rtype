#include "../inc/Sprite.hpp"

Sprite::Sprite(std::string path, sf::Vector2f pos) : m_path(path) {
  if (!m_texture.loadFromFile(m_path))
    std::cout << "Can't find image: " << m_path << std::endl;
  m_sprite.setTexture(m_texture);
  m_sprite.setPosition(pos.x, pos.y);
}

Sprite::~Sprite() {}
