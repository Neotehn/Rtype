/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** menu
*/

#include "../inc/Menu.hpp"

Menu::Menu(sf::VideoMode mode)
    : m_window(mode, "R-Type"),
      m_in_game(false),
      m_start_btn(Button("./src/gameEngine/assets/startBtn.png", 825, 540)) {}

void Menu::handleEvents() {
  sf::Event event;
  while (m_window.pollEvent(event)) {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(m_window);
    sf::Vector2f mouse_pos_f(static_cast<float>(mouse_pos.x),
                             static_cast<float>(mouse_pos.y));
    if (event.type == sf::Event::Closed) m_window.close();
    if (event.type == sf::Event::MouseMoved) {
      m_start_btn.is_hovered(mouse_pos_f);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      if (m_start_btn.is_pressed(mouse_pos_f))
        std::cout << "btn pressed" << std::endl;
    }
  }
}

void Menu::display() {
  m_window.clear();
  m_window.draw(m_start_btn.getSprite());
  m_window.display();
}

void Menu::runMenu() {
  while (m_window.isOpen()) {
    if (!m_in_game) {
      handleEvents();
      display();
    } else {
      // run game
    }
  }
}