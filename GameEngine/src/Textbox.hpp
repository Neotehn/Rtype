/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** Textbox
*/

#ifndef TEXTBOX_HPP_
#define TEXTBOX_HPP_

#include <iostream>
#include <sstream>

#include "../../Game/Encapsulation/IFont.hpp"
#include "../../Game/Encapsulation/IText.hpp"
#include "../../Game/Encapsulation/Event.hpp"
#include "../../Game/Encapsulation/IGraphicLoader.hpp"
#include "../../Game/Encapsulation/GraphicDataTypes.hpp"

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox {
 public:
  Textbox();
  Textbox(int t_size, rtype::Color t_color, bool t_sel,
          rtype::IGraphicLoader *t_graphic_loader);

  void setFont(rtype::IFont *t_font);
  void setPosition(const rtype::Vector2f &t_position);
  void setLimit(bool t_has_limit);
  void setLimit(bool t_has_limit, int t_limit);
  void setSelected(bool t_sel);
  rtype::IText *getText();
  void typedOn(rtype::Event t_input);
  int getLength();

 private:
  rtype::IFont *m_font;
  std::ostringstream m_text;
  rtype::IText *m_textbox;
  bool m_is_selected = false;
  bool m_has_limit = false;
  int m_limit;
  rtype::IGraphicLoader *m_graphic_loader;

  void inputLogic(int t_char_typed);
  void deleteLastChar();
};

#endif /* !TEXTBOX_HPP_ */
