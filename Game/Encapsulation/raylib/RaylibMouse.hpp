#ifndef R_TYPE_CLIENT_RAYLIBMOUSE_HPP
#define R_TYPE_CLIENT_RAYLIBMOUSE_HPP

#include <raylib.h>

#include "../IMouse.hpp"
#include "./RaylibWindow.hpp"

namespace rtype {
  class RaylibMouse : public IMouse {
   public:
    ~RaylibMouse() override = default;

    bool isLeftMouseButtonPressed() const override;
    bool isRightMouseButtonPressed() const override;
    bool isMouseXButton1Pressed() const override;
    bool isMouseXButton2Pressed() const override;
    bool isMouseMiddleButtonPressed() const override;

    rtype::Vector2i
    getMousePosition(rtype::IRenderWindow *m_window) const override;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_RAYLIBMOUSE_HPP
