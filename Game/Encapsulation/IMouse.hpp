#ifndef R_TYPE_CLIENT_IMOUSE_HPP
#define R_TYPE_CLIENT_IMOUSE_HPP

#include "./GraphicDataTypes.hpp"
#include "./IRenderWindow.hpp"

namespace rtype {
  class IMouse {
   public:
    virtual ~IMouse() = default;

    virtual bool isLeftMouseButtonPressed() const = 0;
    virtual rtype::Vector2i
    getMousePosition(rtype::IRenderWindow *m_window) const = 0;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_IMOUSE_HPP
