#ifndef R_TYPE_CLIENT_GRAPHICLOADER_HPP
#define R_TYPE_CLIENT_GRAPHICLOADER_HPP

#include "../IGraphicLoader.hpp"

#include "./Mouse.hpp"
#include "./Music.hpp"
#include "./RectangleShape.hpp"
#include "./RenderWindow.hpp"
#include "./Sounds.hpp"
#include "./Sprite.hpp"
#include "./Texture.hpp"

namespace rtype {
  class GraphicLoader : public IGraphicLoader {
   public:
    GraphicLoader() = default;
    ~GraphicLoader() override = default;

    IMouse *loadMouse() override;
    IMusic *loadMusic() override;
    IRectangleShape *loadRectangleShape() override;
    IRenderWindow *loadRenderWindow() override;
    ISounds *loadSound() override;
    ISprite *loadSprite() override;
    ITexture *loadTexture() override;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_GRAPHICLOADER_HPP
