#include "EventQueue.hpp"
#include "iostream"

EventQueue::EventQueue(std::vector<std::shared_ptr<Action>> t_eventQueue)
    : m_eventQueue(t_eventQueue) {}

EventQueue::EventQueue() {
  m_eventQueue = std::vector<std::shared_ptr<Action>>();
}

EventQueue::~EventQueue() {}

bool EventQueue::checkIfKeyPressed(Action::ActionType t_type) {
  for (int i = 0; i < this->m_eventQueue.size(); i++) {
    if (this->m_eventQueue[i].get()->getType() == t_type) return true;
  }
  return false;
}

std::vector<std::shared_ptr<Action>>
EventQueue::getAllOfType(Action::ActionType t_type) {
  std::vector<std::shared_ptr<Action>> actions;
  for (int i = 0; i < this->m_eventQueue.size(); i++) {
    if (this->m_eventQueue[i].get()->getType() == t_type) {
      actions.push_back(this->m_eventQueue[i]);
    }
  }
  return actions;
}

void EventQueue::setEventQueue(
  std::vector<std::shared_ptr<Action>> t_eventQueue) {
  m_eventQueue = std::move(t_eventQueue);
}
const std::vector<std::shared_ptr<Action>> &EventQueue::getEventQueue() const {
  return m_eventQueue;
}

void EventQueue::addToQueue(std::shared_ptr<Action> t_event) {
  m_eventQueue.push_back(t_event);
}

void EventQueue::addToQueueIfNotExist(std::shared_ptr<Action> t_event,
                                      Action::ActionType t_type) {
  if (!checkIfKeyPressed(t_type)) m_eventQueue.push_back(t_event);
}

bool EventQueue::empty() { return m_eventQueue.empty(); }

void EventQueue::clear() { m_eventQueue.clear(); }

sf::Vector2f EventQueue::getLatestPos(EntityID t_id) {
  sf::Vector2f pos = {0, 0};
  for (std::shared_ptr<Action> event : m_eventQueue) {
    if (event.get()->getType() == Action::ActionType::POS) {
      pos = event.get()->getCreatePosition();
    }
  }
  return pos;
}

void EventQueue::dump() {
  for (std::shared_ptr<Action> event : m_eventQueue) {
    std::cout << event->getTypeAsString() << std::endl;
  }
}
