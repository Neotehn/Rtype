#ifndef CLIENT_SRC_EVENTQUEUE_HPP_
#define CLIENT_SRC_EVENTQUEUE_HPP_

#include <iostream>
#include <memory>
#include <vector>

#include "../Client/src/Action/Action.hpp"

class EventQueue {
 public:
  EventQueue(std::vector<std::shared_ptr<Action>> t_eventQueue);
  EventQueue();
  ~EventQueue();

  const std::vector<std::shared_ptr<Action>> &getEventQueue() const;

  bool empty();
  void clear();
  void dump();
  void addToQueue(std::shared_ptr<Action> t_event);
  void addToQueueIfNotExist(std::shared_ptr<Action> t_event,
                            Action::ActionType t_type);
  void setEventQueue(std::vector<std::shared_ptr<Action>> t_eventQueue);
  bool checkIfKeyPressed(Action::ActionType t_actionType);
  std::vector<std::shared_ptr<Action>> getAllOfType(Action::ActionType t_type);
  void removeEvent(int t_action_id);

  rtype::Vector2f getLatestPos(EntityID t_id);

 private:
  std::vector<std::shared_ptr<Action>> m_eventQueue;
};

#endif  // CLIENT_SRC_EVENTQUEUE_HPP_
