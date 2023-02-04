#ifndef CLIENT_SRC_INPUTMANAGER_INPUTMANAGER_HPP_
#define CLIENT_SRC_INPUTMANAGER_INPUTMANAGER_HPP_

#include <memory>
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
  void addActionsToQueue(std::shared_ptr<IAction> t_action);
  void popInputs();

  EventQueue getInputs();
  sf::Vector2i getMousePosition();
  bool isMouseLeftClicked();
  bool isMouseRightClicked();

 private:
  EntityID m_player_id;
  std::vector<std::shared_ptr<IAction>> m_input_queue;
};

#endif  // CLIENT_SRC_INPUTMANAGER_INPUTMANAGER_HPP_
