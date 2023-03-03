#include "./State.hpp"

State::State(StateMachine &t_machine, rtype::IRenderWindow *t_window,
             MusicPlayer &t_music_player,
             rtype::IGraphicLoader *t_graphic_loader, int *t_level,
             const std::string &t_path_to_sprite,
             const std::string &t_player_name, const bool t_replace,
             std::string t_ip, UdpClient *t_clientCom)
    : m_state_machine(t_machine), m_window(t_window), m_level(t_level),
      m_music_player(t_music_player), m_replace(t_replace) {
  m_graphic_loader = t_graphic_loader;
  m_mouse = m_graphic_loader->loadMouse();
  m_ip = t_ip;
  m_clientCom = t_clientCom;
  m_path_to_sprite = t_path_to_sprite;
  m_player_name = t_player_name;
}

std::unique_ptr<State> State::next() { return std::move(m_next); }

const bool State::isReplacing() { return m_replace; }
