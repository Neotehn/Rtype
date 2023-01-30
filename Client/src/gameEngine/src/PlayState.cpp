#include "../inc/PlayState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "../inc/MainState.hpp"
#include "../inc/StateMachine.hpp"

PlayState::PlayState(StateMachine &machine, sf::RenderWindow &window,
                     const bool replace)
    : State{machine, window, replace} {
  if (!m_backgroundTexture.loadFromFile("./src/gameEngine/assets/play.jpg")) {
    throw std::runtime_error{"Was unable to load image 'img/play.png'"};
  }
  float scale_x = 1280.0 / m_backgroundTexture.getSize().x;
  float scale_y = 720.0 / m_backgroundTexture.getSize().y;
  m_background.setTexture(m_backgroundTexture, true);
  m_background.setScale(scale_x, scale_y);
  std::cout << "PlayState Init\n";
}

void PlayState::pause() { std::cout << "PlayState Pause\n"; }

void PlayState::resume() { std::cout << "PlayState Resume\n"; }

void PlayState::update() {
  for (auto event = sf::Event{}; m_window.pollEvent(event);) {
    switch (event.type) {
      case sf::Event::Closed:
        m_state_machine.quit();
        break;

      case sf::Event::KeyPressed:
        switch (event.key.code) {
          case sf::Keyboard::Escape:
            m_state_machine.quit();
            break;

          case sf::Keyboard::M:
            m_next = StateMachine::build<MainState>(m_state_machine, m_window,
                                                    false);
            break;

          default:
            break;
        }
        break;

      default:
        break;
    }
  }
}

void PlayState::draw() {
  // Clear the previous drawing
  m_window.clear();
  m_window.draw(m_background);
  m_window.display();
}