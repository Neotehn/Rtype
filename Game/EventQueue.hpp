#ifndef CLIENT_SRC_EVENTQUEUE_HPP_
#define CLIENT_SRC_EVENTQUEUE_HPP_

#include <vector>

#include "../Client/src/Action/IAction.hpp"

class EventQueue {
 public:
  EventQueue(std::vector<IAction> t_eventQueue);
  EventQueue();
  ~EventQueue();

  void setEventQueue(std::vector<IAction> t_eventQueue);
  bool checkIfKeyPressed(IAction::ActionType t_actionType);

 private:
  std::vector<IAction> m_eventQueue;

 public:
  const std::vector<IAction> &getEventQueue() const;
};

#endif  // CLIENT_SRC_EVENTQUEUE_HPP_
