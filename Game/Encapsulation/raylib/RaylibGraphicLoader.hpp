#ifndef R_TYPE_CLIENT_RAYLIBGRAPHICLOADER_HPP
#define R_TYPE_CLIENT_RAYLIBGRAPHICLOADER_HPP

#include "../IGraphicLoader.hpp"

#include "./RaylibFont.hpp"
#include "./RaylibMouse.hpp"
#include "./RaylibMusic.hpp"
#include "./RaylibRectangleShape.hpp"
#include "./RaylibWindow.hpp"
#include "./RaylibSound.hpp"
#include "./RaylibSprite.hpp"
#include "./RaylibText.hpp"
#include "./RaylibTexture.hpp"

namespace rtype {

  class RaylibGraphicLoader : public IGraphicLoader {
   public:
    RaylibGraphicLoader() = default;
    ~RaylibGraphicLoader() override = default;

    IFont *loadFont() override;
    IMouse *loadMouse() override;
    IMusic *loadMusic() override;
    IRectangleShape *loadRectangleShape() override;
    IRenderWindow *loadRenderWindow() override;
    ISounds *loadSound() override;
    ISprite *loadSprite() override;
    IText *loadText() override;
    ITexture *loadTexture() override;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_RAYLIBGRAPHICLOADER_HPP
