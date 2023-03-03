#ifndef R_TYPE_CLIENT_MOUSE_HPP
#define R_TYPE_CLIENT_MOUSE_HPP

#include <SFML/Window/Mouse.hpp>

#include "../IMouse.hpp"
#include "./RenderWindow.hpp"

namespace rtype {
  class Mouse : public IMouse {
   public:
    ~Mouse() override = default;

    bool isLeftMouseButtonPressed() const override;
    bool isRightMouseButtonPressed() const override;
    bool isMouseXButton1Pressed() const override;
    bool isMouseXButton2Pressed() const override;
    bool isMouseMiddleButtonPressed() const override;

    rtype::Vector2i
    getMousePosition(rtype::IRenderWindow *m_window) const override;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_MOUSE_HPP
