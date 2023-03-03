/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** IFont
*/

#ifndef IFONT_HPP_
#define IFONT_HPP_

#include <string>

#include "./GraphicDataTypes.hpp"

namespace rtype {
  class IFont {
   public:
    virtual ~IFont() = default;

    virtual bool loadFromFile(const std::string &filename) = 0;
  };
}  // namespace rtype

#endif /* !IFONT_HPP_ */
