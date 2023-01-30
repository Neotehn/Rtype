/*
** EPITECH PROJECT, 2023
** StateMachine
** File description:
** Core
*/

#include "../inc/Core.hpp"
#include "../inc/MainState.hpp"

void Core::run()
{
    m_window.create({1280, 720}, "R-Type", sf::Style::Titlebar | sf::Style::Close);
    m_window.setFramerateLimit(30);

    m_state_machine.run(StateMachine::build<MainState>(m_state_machine, m_window, true));

    while (m_state_machine.running())
    {
        m_state_machine.nextState();
        m_state_machine.update();
        m_state_machine.draw();
    }
}
