/*
** EPITECH PROJECT, 2022
** .
** File description:
** .
*/
#ifndef CLIENT_SRC_INPUTMANAGER_INPUTMANAGER_HPP_
#define CLIENT_SRC_INPUTMANAGER_INPUTMANAGER_HPP_

#include <SFML/Graphics.hpp>
#include "../EventQueue.hpp"

class InputManager {
 public:
  InputManager();
  ~InputManager(){};

  // Get input
  int recordInput();
  void recordInputs(const sf::Event &t_event);
  void popInputs();

  EventQueue getInputs();
  sf::Vector2i getMousePosition();
  bool isMouseLeftClicked();
  bool isMouseRightClicked();

 private:
  std::vector<int> m_input_queue;
};

#endif  // CLIENT_SRC_INPUTMANAGER_INPUTMANAGER_HPP_
