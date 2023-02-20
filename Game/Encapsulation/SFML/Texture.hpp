#ifndef R_TYPE_CLIENT_TEXTURE_HPP
#define R_TYPE_CLIENT_TEXTURE_HPP

#include <SFML/Graphics.hpp>

#include "../ITexture.hpp"

namespace rtype {
  class Texture : public ITexture {
   public:
    Texture();
    Texture(const sf::Texture &texture);
    ~Texture() = default;

    bool loadFromFile(const std::string &filename) override;
    bool loadFromFile(const std::string &filename,
                      const IntRect &area = IntRect()) override;

    rtype::Vector2u getSize() const override;

    const sf::Texture *getTexture();

   private:
    sf::Texture *m_texture;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_TEXTURE_HPP
