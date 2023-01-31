/*
** EPITECH PROJECT, 2023
** StateMachine
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <SFML/Graphics/RenderWindow.hpp>

#include "StateMachine.hpp"

class Core {
 public:
  Core();
  void run();

 private:
  sf::RenderWindow m_window;
  StateMachine m_state_machine;
};

#endif /* !CORE_HPP_ */
