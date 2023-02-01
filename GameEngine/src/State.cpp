#include "../inc/State.hpp"

State::State(StateMachine &t_machine, sf::RenderWindow &t_window,
             const bool t_replace)
    : m_state_machine(t_machine), m_window(t_window), m_replace(t_replace) {}

std::unique_ptr<State> State::next() { return std::move(m_next); }

const bool State::isReplacing() { return m_replace; }