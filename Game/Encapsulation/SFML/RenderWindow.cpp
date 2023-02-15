#include "./RenderWindow.hpp"

rtype::RenderWindow::RenderWindow() {}

rtype::RenderWindow::RenderWindow(unsigned int t_width, unsigned int t_height,
                                  std::string t_title) {
  create(t_width, t_height, t_title);
}

rtype::RenderWindow::~RenderWindow() {}

void rtype::RenderWindow::draw(sf::Sprite t_sprite) { m_window.draw(t_sprite); }

// TODO: how to handle this?
void rtype::RenderWindow::draw(sf::RectangleShape t_shape) {
  m_window.draw(t_shape);
}

void rtype::RenderWindow::display() { m_window.display(); }

rtype::Vector2u rtype::RenderWindow::getSize() const {
  return {m_window.getSize().x, m_window.getSize().y};
}

bool rtype::RenderWindow::isOpen() { return m_window.isOpen(); }

void rtype::RenderWindow::close() { m_window.close(); }

void rtype::RenderWindow::clear(rtype::Color t_color) {
  m_window.clear(sf::Color(t_color.r, t_color.g, t_color.b, t_color.a));
}

void rtype::RenderWindow::setFramerateLimit(unsigned int t_fps) {
  m_window.setFramerateLimit(t_fps);
}

void rtype::RenderWindow::create(unsigned int t_width, unsigned int t_height,
                                 std::string t_title) {
  m_window.create(sf::VideoMode(t_width, t_height), t_title);
}

bool rtype::RenderWindow::pollEvent(rtype::Event &t_event) {
  bool res = m_window.pollEvent(m_event);
  t_event.type = rtype::EventType(m_event.type);
  t_event.key = rtype::EventKey(m_event.key.code);
  return res;
}
