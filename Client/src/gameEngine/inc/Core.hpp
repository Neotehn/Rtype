/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>

#include "Menu.hpp"
#include "Settings.hpp"

class Core {
 public:
  Core(sf::VideoMode mode = sf::VideoMode(1280, 720));
  ~Core();

  void loop();

 private:
  sf::RenderWindow m_window;
  Menu m_main_menu;
  Settings m_settings;
  int m_x_res;
  int m_y_res;
  int m_screen;
};

#endif /* !CORE_HPP_ */
