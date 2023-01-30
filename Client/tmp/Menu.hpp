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
#include "Sprite.hpp"

class Menu : public Sprite {
 public:
  Menu(sf::RenderWindow &window);
  int runMenu();
  void setSettings(bool x) { m_in_settings = x; }
  void setGame(bool x) { m_in_game = x; }

 private:
  void display();
  void handleEvents();

  sf::RenderWindow &m_window;
  bool m_in_game;
  bool m_in_settings;
  sf::Font m_font;
  Button m_start_btn;
  Button m_settings_btn;
};

#endif /* !MENU_HPP_ */
