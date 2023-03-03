#include "GraphicLoader.hpp"

rtype::IFont *rtype::GraphicLoader::loadFont() { return new Font(); }

rtype::IMouse *rtype::GraphicLoader::loadMouse() { return new Mouse(); }

rtype::IMusic *rtype::GraphicLoader::loadMusic() { return new Music(); }

rtype::IRectangleShape *rtype::GraphicLoader::loadRectangleShape() {
  return new RectangleShape();
}

rtype::IRenderWindow *rtype::GraphicLoader::loadRenderWindow() {
  return new RenderWindow();
}

rtype::ISounds *rtype::GraphicLoader::loadSound() { return new Sounds(); }

rtype::ISprite *rtype::GraphicLoader::loadSprite() { return new Sprite(); }

rtype::IText *rtype::GraphicLoader::loadText() { return new Text(); }

rtype::ITexture *rtype::GraphicLoader::loadTexture() { return new Texture(); }
