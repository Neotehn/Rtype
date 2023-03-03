#include "./RenderWindow.hpp"

rtype::RenderWindow::RenderWindow() {}

rtype::RenderWindow::RenderWindow(unsigned int t_width, unsigned int t_height,
                                  std::string t_title) {
  create(t_width, t_height, t_title);
}

rtype::RenderWindow::~RenderWindow() {}

void rtype::RenderWindow::draw(const rtype::ISprite *t_sprite) {
  rtype::ISprite *sprite = const_cast<rtype::ISprite *>(t_sprite);

  m_window.draw(dynamic_cast<rtype::Sprite *>(sprite)->getSprite());
}

void rtype::RenderWindow::draw(rtype::IRectangleShape *t_shape) {
  m_window.draw(
    dynamic_cast<rtype::RectangleShape *>(t_shape)->getRectangleShape());
}

void rtype::RenderWindow::draw(const rtype::IText *t_text) {
  rtype::IText *text = const_cast<rtype::IText *>(t_text);
  m_window.draw(dynamic_cast<rtype::Text *>(text)->getText());
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

void rtype::RenderWindow::create(unsigned int t_width, unsigned int t_height,
                                 std::string t_title, rtype::Style t_style) {
  m_window.create(sf::VideoMode(t_width, t_height), t_title, t_style);
}

bool rtype::RenderWindow::pollEvent(rtype::Event &t_event) {
  bool res = m_window.pollEvent(m_event);
  t_event.type = rtype::EventType(m_event.type);
  t_event.key = rtype::EventKey(m_event.key.code);
  return res;
}

sf::RenderWindow *rtype::RenderWindow::getRenderWindow() { return &m_window; }
