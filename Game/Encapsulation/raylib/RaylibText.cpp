#include "RaylibText.hpp"

namespace rtype {
  void RaylibText::setFont(rtype::IFont *font) {
    m_font = dynamic_cast<rtype::RaylibFont *>(font);
  }

  void RaylibText::setPosition(const rtype::Vector2f &position) {
    m_position = position;
  }

  void RaylibText::setString(const std::string &string) { m_text = string; }

  void RaylibText::setCharacterSize(unsigned int size) { m_size = size; }

  void RaylibText::setColor(const rtype::Color &color) { m_color = color; }

  const rtype::IFont *RaylibText::getFont() const { return m_font; }

  unsigned int RaylibText::getCharacterSize() const { return m_size; }

  void RaylibText::setScale(const rtype::Vector2f &factor) { m_scale = factor; }

  const rtype::Vector2f &RaylibText::getPosition() const { return m_position; }

  const std::string &RaylibText::getString() const { return m_text; }

  rtype::FloatRect RaylibText::getLocalBounds() const {
    Vector2 size =
      MeasureTextEx(m_font->getFont(), m_text.c_str(), m_size, 1.0f);
    return rtype::FloatRect{m_position.x, m_position.y, size.x, size.y};
  }

  rtype::Color RaylibText::getColor() const { return m_color; }
}  // namespace rtype
