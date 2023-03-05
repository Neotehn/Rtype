#include "RaylibMouse.hpp"

rtype::Vector2i
rtype::RaylibMouse::getMousePosition(rtype::IRenderWindow *m_window) const {
  Vector2 mousePos = GetMousePosition();
  return rtype::Vector2i{static_cast<int>(mousePos.x),
                         static_cast<int>(mousePos.y)};
}

bool rtype::RaylibMouse::isLeftMouseButtonPressed() const {
  return IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

bool rtype::RaylibMouse::isRightMouseButtonPressed() const {
  return IsMouseButtonPressed(MOUSE_RIGHT_BUTTON);
}

bool rtype::RaylibMouse::isMouseXButton1Pressed() const {
  return IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON);
}

bool rtype::RaylibMouse::isMouseXButton2Pressed() const {
  return IsMouseButtonPressed(MOUSE_BUTTON_EXTRA);
}

bool rtype::RaylibMouse::isMouseMiddleButtonPressed() const {
  return IsMouseButtonPressed(MOUSE_BUTTON_SIDE);
}
