/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** Settings
*/

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>

#include "Button.hpp"
#include "Sprite.hpp"

class Settings : public Sprite {
 public:
  Settings(sf::RenderWindow &window);
  ~Settings();
  int runSettings();

 private:
  void display();
  void handleEvents();
  sf::RenderWindow &m_window;
  Button m_btn_main;
  bool m_in_settings;
};

#endif /* !SETTINGS_HPP_ */
