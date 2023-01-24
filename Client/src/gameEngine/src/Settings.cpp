/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** Settings
*/

#include "../inc/Settings.hpp"

Settings::Settings(sf::RenderWindow &window)
    : m_window(window),
      m_in_settings(true),
      Sprite("./src/gameEngine/assets/menubg.jpg", sf::Vector2f(0, 0)),
      m_btn_main((Button("./src/gameEngine/assets/startBtn.png",
                         sf::Vector2f(600, 350), sf::Vector2f(270, 130)))) {
  float pos_x = 1280.0 / getTexture().getSize().x;
  float pos_y = 720.0 / getTexture().getSize().y;
  getSprite().setScale(pos_x, pos_y);
}

Settings::~Settings() {}

void Settings::handleEvents() {
  sf::Event event;
  while (m_window.pollEvent(event)) {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(m_window);
    sf::Vector2f mouse_pos_f(static_cast<float>(mouse_pos.x),
                             static_cast<float>(mouse_pos.y));
    if (event.type == sf::Event::Closed) m_window.close();
    if (event.type == sf::Event::MouseMoved) {
      m_btn_main.is_hovered(mouse_pos_f);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      if (m_btn_main.is_pressed(mouse_pos_f))
        std::cout << "backbtn pressed" << std::endl;
      m_in_settings = false;
    }
  }
}

void Settings::display() {
  m_window.clear();
  m_window.draw(getSprite());
  m_window.draw(m_btn_main.getSprite());
  m_window.display();
}

int Settings::runSettings() {
  if (m_in_settings) {
    handleEvents();
    display();
  } else {
    m_in_settings = true;
    return 0;
  }
  return 1;
}
