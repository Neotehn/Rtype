/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** IText
*/

#ifndef ITEXT_HPP_
#define ITEXT_HPP_

#include <string>

#include "./GraphicDataTypes.hpp"
#include "./IFont.hpp"

namespace rtype {
  class IText {
   public:
    virtual ~IText() = default;

    virtual void setFont(rtype::IFont *font) = 0;
    virtual void setPosition(const rtype::Vector2f &position) = 0;
    virtual void setString(const std::string &string) = 0;
    virtual void setCharacterSize(unsigned int size) = 0;
    virtual void setColor(const rtype::Color &color) = 0;
    virtual const rtype::IFont *getFont() const = 0;
    virtual unsigned int getCharacterSize() const = 0;
    // virtual const rtype::Color &getColor() const = 0;
    virtual void setScale(const rtype::Vector2f &factor) = 0;
    virtual const rtype::Vector2f &getPosition() const = 0;
    virtual const std::string &getString() const = 0;
    virtual rtype::FloatRect getLocalBounds() const = 0;
  };
}  // namespace rtype

#endif /* !ITEXT_HPP_ */
