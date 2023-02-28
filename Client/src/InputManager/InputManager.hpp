#ifndef CLIENT_SRC_INPUTMANAGER_INPUTMANAGER_HPP_
#define CLIENT_SRC_INPUTMANAGER_INPUTMANAGER_HPP_

#include <memory>
#include <vector>

#include "../Action/Action.hpp"
#include "../Action/MovementAction.hpp"
#include "../Action/ShootAction.hpp"
#include "../Action/StateAction.hpp"
#include "../../../Game/EventQueue.hpp"
#include "../../../Game/Encapsulation/Event.hpp"

class InputManager {
 public:
  InputManager(int *t_level);
  ~InputManager(){};

  void recordInputs(const rtype::Event &t_event);
  void recordKeyPressedInputs(const rtype::Event &t_event);
  void recordKeyReleasedInputs(const rtype::Event &t_event);
  void addActionsToQueue(std::shared_ptr<Action> t_action);
  void popInputs();
  void removeEvent(int t_action_id);

  EventQueue getInputs();
  EventQueue getInputsWithoutPop();
  bool doesActionExist(std::shared_ptr<Action> t_action_id);
  bool isPlayerIdSet();
  void setPlayerId(EntityID t_player_id);
  int *m_level;

 private:
  EntityID m_player_id = 0;
  EventQueue m_input_queue;
};

#endif  // CLIENT_SRC_INPUTMANAGER_INPUTMANAGER_HPP_
