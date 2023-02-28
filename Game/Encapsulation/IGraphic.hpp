#ifndef R_TYPE_CLIENT_IGRAPHIC_HPP
#define R_TYPE_CLIENT_IGRAPHIC_HPP

#include "GraphicDataTypes.hpp"
#include "SFML/RenderWindow.hpp"

namespace rtype {
  class IGraphic {
   public:
    virtual ~IGraphic() = default;
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void updateData() = 0;

   private:
    rtype::RenderWindow m_window;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_IGRAPHIC_HPP
