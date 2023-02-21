#ifndef R_TYPE_CLIENT_ITEXTURE_HPP
#define R_TYPE_CLIENT_ITEXTURE_HPP

#include <string>

#include "./GraphicDataTypes.hpp"

namespace rtype {
  class ITexture {
   public:
    virtual ~ITexture() = default;

    virtual bool loadFromFile(const std::string &filename) = 0;
    virtual bool loadFromFile(const std::string &filename,
                              const IntRect &area) = 0;

    virtual rtype::Vector2u getSize() const = 0;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_ITEXTURE_HPP
