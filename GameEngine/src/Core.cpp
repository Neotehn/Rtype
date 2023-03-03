#include "./Core.hpp"

Core::Core(std::size_t t_flag, std::string t_ip, const std::string& t_path ,int *t_level) {
  m_graphic_loader = new rtype::GraphicLoader();
  m_music_player.init(m_graphic_loader);
  m_window = m_graphic_loader->loadRenderWindow();
  m_window->create(
    800, 800, t_flag == 0 ? "R-Type Server" : "R-Type Client",
    static_cast<rtype::Style>(rtype::Style::Titlebar | rtype::Style::Close));
  m_window->setFramerateLimit(60);
  srand(time(nullptr));

  if (t_flag == 1) {
    m_port_number = rand() % 15000 + 40001;
    std::cout << t_ip << std::endl;
    m_clientCom = new UdpClient(m_io_service, t_ip, "55555", m_port_number);
    m_state_machine.run(StateMachine::build<IntroState>(
      m_state_machine, m_window, m_music_player, t_flag, m_graphic_loader,
      t_level, t_path, true, t_ip, m_clientCom));
  } else
    m_state_machine.run(StateMachine::build<GameState>(
      m_state_machine, m_window, m_music_player, t_flag, m_graphic_loader,
      t_level, "", true, t_ip));

}

Core::~Core() {
  if (m_graphic_loader) delete m_graphic_loader;
}

void Core::run() {
  while (m_state_machine.running()) {
    m_state_machine.nextState();
    m_state_machine.update();
    m_state_machine.draw();
  }
}
