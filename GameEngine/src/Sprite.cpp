#include "../inc/Sprite.hpp"

Sprite::Sprite(std::string t_path, sf::Vector2f t_pos) : m_path(t_path) {
  if (!m_texture.loadFromFile(m_path))
    std::cout << "Can't find image: " << m_path << std::endl;
  m_sprite.setTexture(m_texture);
  m_sprite.setPosition(t_pos.x, t_pos.y);
}

Sprite::~Sprite() {}
