#include "EventQueue.hpp"
#include "iostream"

EventQueue::EventQueue(std::vector<std::shared_ptr<IAction>> t_eventQueue)
    : m_eventQueue(t_eventQueue) {}

EventQueue::EventQueue() {
  m_eventQueue = std::vector<std::shared_ptr<IAction>>();
}

EventQueue::~EventQueue() {}

bool EventQueue::checkIfKeyPressed(IAction::ActionType t_type) {
  for (int i = 0; i < this->m_eventQueue.size(); i++) {
    if (this->m_eventQueue[i].get()->getType() == t_type) return true;
  }
  return false;
}

void EventQueue::setEventQueue(
  std::vector<std::shared_ptr<IAction>> t_eventQueue) {
  m_eventQueue = std::move(t_eventQueue);
}
const std::vector<std::shared_ptr<IAction>> &EventQueue::getEventQueue() const {
  return m_eventQueue;
}
