/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** Text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include <SFML/Graphics/Text.hpp>

#include "../IText.hpp"
#include "./Font.hpp"

namespace rtype {
  class Text : public IText {
   public:
    Text() = default;
    ~Text() override = default;

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
    sf::Text &getText();

   private:
    sf::Text m_text;
  };
}  // namespace rtype

#endif /* !TEXT_HPP_ */
