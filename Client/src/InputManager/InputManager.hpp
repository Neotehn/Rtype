#ifndef CLIENT_SRC_INPUTMANAGER_INPUTMANAGER_HPP_
#define CLIENT_SRC_INPUTMANAGER_INPUTMANAGER_HPP_

#include <vector>
#include <SFML/Graphics.hpp>

#include "../Action/IAction.hpp"
#include "../Action/MovementAction.hpp"
#include "../Action/ShootAction.hpp"
#include "../../../Game/EventQueue.hpp"

class InputManager {
 public:
  InputManager();
  ~InputManager(){};

  void recordInputs(const sf::Event &t_event);
  void popInputs();

  EventQueue getInputs();
  sf::Vector2i getMousePosition();
  bool isMouseLeftClicked();
  bool isMouseRightClicked();

 private:
  EntityID m_player_id;
  std::vector<IAction> m_input_queue;
};

#endif  // CLIENT_SRC_INPUTMANAGER_INPUTMANAGER_HPP_
