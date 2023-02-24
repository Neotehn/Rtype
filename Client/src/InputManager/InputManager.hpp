#ifndef CLIENT_SRC_INPUTMANAGER_INPUTMANAGER_HPP_
#define CLIENT_SRC_INPUTMANAGER_INPUTMANAGER_HPP_

#include <memory>
#include <vector>

#include "../Action/Action.hpp"
#include "../Action/MovementAction.hpp"
#include "../Action/ShootAction.hpp"
#include "../../../Game/EventQueue.hpp"
#include "../../../Game/Encapsulation/Event.hpp"

class InputManager {
 public:
  InputManager();
  ~InputManager(){};

  void recordInputs(const rtype::Event &t_event);
  void addActionsToQueue(std::shared_ptr<Action> t_action);
  void popInputs();

  EventQueue getInputs();
  EventQueue getInputsWithoutPop();
  bool doesActionExist(std::shared_ptr<Action> t_action_id);
  bool isPlayerIdSet();
  void setPlayerId(EntityID t_player_id);
  // TODO: encapsulate sf::Mouse
  //  sf::Vector2i getMousePosition();
  //  bool isMouseLeftClicked();
  //  bool isMouseRightClicked();

 private:
  EntityID m_player_id = 0;
  EventQueue m_input_queue;
};

#endif  // CLIENT_SRC_INPUTMANAGER_INPUTMANAGER_HPP_
