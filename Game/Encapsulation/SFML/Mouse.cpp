#include "Mouse.hpp"

rtype::Vector2i
rtype::Mouse::getMousePosition(rtype::IRenderWindow *m_window) const {
  sf::Vector2i mousePos = sf::Mouse::getPosition(
    *(dynamic_cast<rtype::RenderWindow *>(m_window))->getRenderWindow());
  return rtype::Vector2i{mousePos.x, mousePos.y};
}

bool rtype::Mouse::isLeftMouseButtonPressed() const {
  return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

bool rtype::Mouse::isRightMouseButtonPressed() const {
  return sf::Mouse::isButtonPressed(sf::Mouse::Right);
}

bool rtype::Mouse::isMouseXButton1Pressed() const {
  return sf::Mouse::isButtonPressed(sf::Mouse::XButton1);
}

bool rtype::Mouse::isMouseXButton2Pressed() const {
  return sf::Mouse::isButtonPressed(sf::Mouse::XButton2);
}

bool rtype::Mouse::isMouseMiddleButtonPressed() const {
  return sf::Mouse::isButtonPressed(sf::Mouse::Middle);
}
