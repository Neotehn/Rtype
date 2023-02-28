#ifndef R_TYPE_CLIENT_IGRAPHICLOADER_HPP
#define R_TYPE_CLIENT_IGRAPHICLOADER_HPP

#include "IMouse.hpp"
#include "IMusic.hpp"
#include "IRectangleShape.hpp"
#include "IRenderWindow.hpp"
#include "ISounds.hpp"
#include "ISprite.hpp"
#include "ITexture.hpp"

namespace rtype {
  class IGraphicLoader {
   public:
    virtual ~IGraphicLoader() = default;

    virtual rtype::IMouse *loadMouse() = 0;
    virtual rtype::IMusic *loadMusic() = 0;
    virtual rtype::IRectangleShape *loadRectangleShape() = 0;
    virtual rtype::IRenderWindow *loadRenderWindow() = 0;
    virtual rtype::ISounds *loadSound() = 0;
    virtual rtype::ISprite *loadSprite() = 0;
    virtual rtype::ITexture *loadTexture() = 0;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_IGRAPHICLOADER_HPP
