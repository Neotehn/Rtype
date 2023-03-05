#ifndef R_TYPE_CLIENT_RAYLIBFONT_HPP
#define R_TYPE_CLIENT_RAYLIBFONT_HPP

#include <raylib.h>

#include "../IFont.hpp"

namespace rtype {

  class RaylibFont : public IFont {
   public:
    RaylibFont();
    RaylibFont(const Font &font);
    ~RaylibFont() = default;

    bool loadFromFile(const std::string &filename) override;

    const Font getFont();

   private:
    Font m_font;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_RAYLIBFONT_HPP
