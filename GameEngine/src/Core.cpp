#include "./Core.hpp"

Core::Core(std::size_t t_flag) {
  m_window = new rtype::RenderWindow();
  m_window->create(
    800, 800, "R-Type",
    static_cast<rtype::Style>(rtype::Style::Titlebar | rtype::Style::Close));
  m_window->setFramerateLimit(30);

  m_state_machine.run(StateMachine::build<MainState>(
    m_state_machine, m_window, m_music_player, t_flag, true));
}

Core::~Core() {}

void Core::run() {
  while (m_state_machine.running()) {
    m_state_machine.nextState();
    m_state_machine.update();
    m_state_machine.draw();
  }
}
