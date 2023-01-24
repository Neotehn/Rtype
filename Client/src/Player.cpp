#include "Player.hpp"

Player::Player(std::string t_sprite_path) {
  loadFromFile(t_sprite_path);
  m_body.setSize({100, 100});
  m_body.setOrigin(m_body.getSize().x / 2, m_body.getSize().y / 2);
  setPosition(m_position.x, m_position.y);
  m_body.setTexture(&m_texture);
  m_body.setRotation(m_angle);
}

bool Player::loadFromFile(std::string t_filepath) {
  if (!m_texture.loadFromFile(t_filepath)) {
    std::cerr << "Error loading sprite" << std::endl;
    return false;
  }
  m_sprite.setTexture(m_texture);
  return true;
}

void Player::display(sf::RenderWindow &t_window) { t_window.draw(m_body); }

void Player::setPosition(float x, float y) {
  m_sprite.setPosition(x, y);
  m_body.setPosition(x, y);
}

void Player::move(sf::Vector2f direction) {
  m_velocity = direction * m_speed;
}

void Player::handlePlayerInput(const sf::Event &t_event) {
  switch (t_event.key.code) {
    case sf::Keyboard::W:
      move(sf::Vector2f(0, -1));
      break;
    case sf::Keyboard::S:
      move(sf::Vector2f(0, 1));
      break;
    case sf::Keyboard::D:
      move(sf::Vector2f(1, 0));
      break;
    case sf::Keyboard::A:
      move(sf::Vector2f(-1, 0));
      break;
  }
}

void Player::update(sf::Vector2f t_window_size) {
  if (m_position.x <= m_body.getSize().x / 2) {
    m_velocity.x = 1;
  } else if (m_position.x + m_body.getSize().x >=
             t_window_size.x + m_body.getSize().x / 2) {
    m_velocity.x = -1;
  }
  if (m_position.y <= m_body.getSize().y / 2) {
    m_velocity.y = 1;
  } else if (m_position.y + m_body.getSize().y >=
             t_window_size.y + m_body.getSize().y / 2) {
    m_velocity.y = -1;
  }
  m_position += m_velocity;
  m_body.setPosition(m_position);
  if (m_velocity.x != 0 || m_velocity.y != 0) m_velocity *= 0.99f;
}
