/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** menu
*/

#include "../inc/Menu.hpp"

#include "../inc/Settings.hpp"

Menu::Menu(sf::RenderWindow &window)
    : m_window(window),
      m_in_game(false),
      m_in_settings(false),
      m_start_btn(Button("./src/gameEngine/assets/startBtn.png",
                         sf::Vector2f(600, 350), sf::Vector2f(270, 130))),
      Sprite("./src/gameEngine/assets/menubg.jpg", sf::Vector2f(0, 0)),
      m_settings_btn(Button("./src/gameEngine/assets/gear.png",
                            sf::Vector2f(1000, 600), sf::Vector2f(64, 64))) {
  float pos_x = 1280.0 / getTexture().getSize().x;
  float pos_y = 720.0 / getTexture().getSize().y;
  getSprite().setScale(pos_x, pos_y);
}

void Menu::handleEvents() {
  sf::Event event;
  while (m_window.pollEvent(event)) {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(m_window);
    sf::Vector2f mouse_pos_f(static_cast<float>(mouse_pos.x),
                             static_cast<float>(mouse_pos.y));
    if (event.type == sf::Event::Closed) m_window.close();
    if (event.type == sf::Event::MouseMoved) {
      m_start_btn.is_hovered(mouse_pos_f);
      m_start_btn.is_hovered(mouse_pos_f);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      if (m_start_btn.is_pressed(mouse_pos_f))
        std::cout << "startbtn pressed" << std::endl;
      if (m_settings_btn.is_pressed(mouse_pos_f)) {
        std::cout << "settingsbtn pressed" << std::endl;
        m_in_settings = true;
      }
    }
  }
}

void Menu::display() {
  m_window.clear();
  m_window.draw(getSprite());
  m_window.draw(m_start_btn.getSprite());
  m_window.draw(m_settings_btn.getSprite());
  m_window.display();
}

int Menu::runMenu() {
  if (!m_in_game && !m_in_settings) {
    handleEvents();
    display();
  } else if (m_in_settings) {
    return 1;
  } else {
    // run game
  }
  return 0;
}
