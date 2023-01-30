/*
** EPITECH PROJECT, 2023
** statemachine
** File description:
** State
*/

#include "../inc/State.hpp"

State::State(StateMachine &machine, sf::RenderWindow &window, const bool replace) : m_state_machine(machine), m_window(window), m_replace(replace)
{
}

std::unique_ptr<State> State::next()
{
    return std::move(m_next);
}

bool State::isReplacing() const
{
    return m_replace;
}