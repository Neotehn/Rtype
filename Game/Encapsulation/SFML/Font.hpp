/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** Font
*/

#ifndef FONT_HPP_
#define FONT_HPP_

#include <SFML/Graphics/Font.hpp>

#include "../IFont.hpp"

namespace rtype {
  class Font : public IFont {
   public:
    Font();
    Font(const sf::Font &font);
    ~Font() = default;

    bool loadFromFile(const std::string &filename) override;

    const sf::Font *getFont();

   private:
    sf::Font *m_font;
  };
}  // namespace rtype

#endif /* !FONT_HPP_ */
