/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** Core
*/

#include "../inc/Core.hpp"

Core::Core(sf::VideoMode mode)
    : m_window(mode, "R-Type"),
      m_x_res(1280),
      m_y_res(720),
      m_main_menu(Menu(m_window)),
      m_settings(m_window),
      m_screen(0) {}

Core::~Core() {}

void Core::loop() {
  while (m_window.isOpen()) {
    switch (m_screen) {
      case (0):
        m_screen = m_main_menu.runMenu();
        break;
      case (1):
        m_screen = m_settings.runSettings();
        m_main_menu.setSettings(false);
        break;
      default:
        break;
    }
  }
}
