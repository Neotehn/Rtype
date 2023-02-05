#ifndef CLIENT_SRC_EVENTQUEUE_HPP_
#define CLIENT_SRC_EVENTQUEUE_HPP_

#include <memory>
#include <vector>

#include "../Client/src/Action/Action.hpp"

class EventQueue {
 public:
  EventQueue(std::vector<std::shared_ptr<Action>> t_eventQueue);
  EventQueue();
  ~EventQueue();

  void setEventQueue(std::vector<std::shared_ptr<Action>> t_eventQueue);
  bool checkIfKeyPressed(Action::ActionType t_actionType);
  std::vector<std::shared_ptr<Action>> getAllOfType(Action::ActionType t_type);

 private:
  std::vector<std::shared_ptr<Action>> m_eventQueue;

 public:
  const std::vector<std::shared_ptr<Action>> &getEventQueue() const;
};

#endif  // CLIENT_SRC_EVENTQUEUE_HPP_
