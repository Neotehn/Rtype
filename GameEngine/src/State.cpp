#include "./State.hpp"

State::State(StateMachine &t_machine, rtype::IRenderWindow *t_window,
             MusicPlayer &t_music_player, const bool t_replace)
    : m_state_machine(t_machine), m_window(t_window),
      m_music_player(t_music_player), m_replace(t_replace) {
  m_mouse = new rtype::Mouse();
}

std::unique_ptr<State> State::next() { return std::move(m_next); }

const bool State::isReplacing() { return m_replace; }
