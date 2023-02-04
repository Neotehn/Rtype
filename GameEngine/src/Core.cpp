#include "../inc/Core.hpp"
#include "../../Client/inc/MainState.hpp"

Core::Core() {
  m_window.create({1280, 720}, "R-Type",
                  sf::Style::Titlebar | sf::Style::Close);
  m_window.setFramerateLimit(30);

  m_state_machine.run(StateMachine::build<MainState>(m_state_machine, m_window,
                                                     m_music_player, true));
}

Core::~Core() {}

void Core::run() {
  while (m_state_machine.running()) {
    m_state_machine.nextState();
    m_state_machine.update();
    m_state_machine.draw();
  }
}
