/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>

#include "Button.hpp"

class Menu {
 public:
  Menu(sf::VideoMode mode);
  void runMenu();

 private:
  void display();
  void handleEvents();

  sf::RenderWindow m_window;
  bool m_in_game;
  sf::Font m_font;
  Button m_start_btn;
};

#endif /* !MENU_HPP_ */
