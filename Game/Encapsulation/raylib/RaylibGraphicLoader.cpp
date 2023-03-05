#include "RaylibGraphicLoader.hpp"

namespace rtype {
  IFont *RaylibGraphicLoader::loadFont() { return new RaylibFont(); }

  IMouse *RaylibGraphicLoader::loadMouse() { return new RaylibMouse(); }

  IMusic *RaylibGraphicLoader::loadMusic() { return new RaylibMusic(); }

  IRectangleShape *RaylibGraphicLoader::loadRectangleShape() {
    return new RaylibRectangleShape();
  }

  IRenderWindow *RaylibGraphicLoader::loadRenderWindow() {
    return new RaylibWindow();
  }

  ISounds *RaylibGraphicLoader::loadSound() { return new RaylibSound(); }

  ISprite *RaylibGraphicLoader::loadSprite() { return new RaylibSprite(); }

  IText *RaylibGraphicLoader::loadText() { return new RaylibText(); }

  ITexture *RaylibGraphicLoader::loadTexture() { return new RaylibTexture(); }
}  // namespace rtype
