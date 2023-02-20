#include "./Sprite.hpp"

Sprite::Sprite(std::string t_path, rtype::Vector2f t_pos) : m_path(t_path) {
  m_texture = new rtype::Texture();
  m_sprite = new rtype::Sprite();
  if (!m_texture->loadFromFile(m_path))
    std::cout << "Can't find image: " << m_path << std::endl;
  m_sprite->setTexture(m_texture);
  m_sprite->setPosition(t_pos);
}

Sprite::~Sprite() {
  delete m_texture;
  delete m_sprite;
}

rtype::ISprite *Sprite::getSprite() { return m_sprite; }

void Sprite::setPos(float t_pos_x, float t_pos_y) {
  m_sprite->setPosition({t_pos_x, t_pos_y});
}

rtype::ITexture *Sprite::getTexture() { return m_texture; }

void Sprite::setPath(std::string t_path) { m_path = t_path; }

std::string &Sprite::getPath() { return m_path; }
