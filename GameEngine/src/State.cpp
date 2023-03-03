#include "./State.hpp"

State::State(StateMachine &t_machine, rtype::IRenderWindow *t_window,
             MusicPlayer &t_music_player,
             rtype::IGraphicLoader *t_graphic_loader, int *t_level,
             const std::string& t_path,
             const bool t_replace)
    : m_state_machine(t_machine), m_window(t_window), m_level(t_level),
      m_music_player(t_music_player),
      m_replace(t_replace) {
  m_graphic_loader = t_graphic_loader;
  m_mouse = m_graphic_loader->loadMouse();
  m_path_to_sprite = t_path;
}

std::unique_ptr<State> State::next() { return std::move(m_next); }

const bool State::isReplacing() { return m_replace; }
