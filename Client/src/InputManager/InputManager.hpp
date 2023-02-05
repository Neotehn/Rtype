#ifndef CLIENT_SRC_INPUTMANAGER_INPUTMANAGER_HPP_
#define CLIENT_SRC_INPUTMANAGER_INPUTMANAGER_HPP_

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../Action/Action.hpp"
#include "../Action/MovementAction.hpp"
#include "../Action/ShootAction.hpp"
#include "../../../Game/EventQueue.hpp"

class InputManager {
 public:
  InputManager();
  ~InputManager(){};

  void recordInputs(const sf::Event &t_event);
  void addActionsToQueue(std::shared_ptr<Action> t_action);
  void popInputs();

  EventQueue getInputs();
  sf::Vector2i getMousePosition();
  bool doesActionExist(std::shared_ptr<Action> t_action_id);
  bool isMouseLeftClicked();
  bool isMouseRightClicked();

 private:
  EntityID m_player_id;
  EventQueue m_input_queue;
};

#endif  // CLIENT_SRC_INPUTMANAGER_INPUTMANAGER_HPP_
