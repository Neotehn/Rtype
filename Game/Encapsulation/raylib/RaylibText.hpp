#ifndef R_TYPE_CLIENT_RAYLIBTEXT_HPP
#define R_TYPE_CLIENT_RAYLIBTEXT_HPP

#include <raylib.h>

#include "../IText.hpp"
#include "./RaylibFont.hpp"

namespace rtype {
  class RaylibText : public IText {
   public:
    RaylibText() = default;
    ~RaylibText() override = default;

    void setFont(rtype::IFont *font) override;
    void setPosition(const rtype::Vector2f &position) override;
    void setString(const std::string &string) override;
    void setCharacterSize(unsigned int size) override;
    void setColor(const rtype::Color &color) override;
    const rtype::IFont *getFont() const override;
    unsigned int getCharacterSize() const override;
    // const rtype::Color &getColor() const override;
    void setScale(const rtype::Vector2f &factor) override;
    const rtype::Vector2f &getPosition() const override;
    const std::string &getString() const override;
    rtype::FloatRect getLocalBounds() const override;
    rtype::Color getColor() const;

   private:
    std::string m_text = "";
    rtype::Vector2f m_position = {0, 0};
    rtype::Color m_color = {255, 255, 255, 255};
    unsigned int m_size = 1;
    rtype::RaylibFont *m_font;
    rtype::Vector2f m_scale = {1, 1};
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_RAYLIBTEXT_HPP
