#include "EventQueue.hpp"
#include "iostream"

EventQueue::EventQueue(std::vector<int> t_eventQueue)
    : m_eventQueue(t_eventQueue) {}

EventQueue::EventQueue() { m_eventQueue = std::vector<int>(); }

EventQueue::~EventQueue() {}

bool EventQueue::checkIfKeyPressed(int key) {
  for (int i = 0; i < this->m_eventQueue.size(); i++) {
    if (this->m_eventQueue[i] == key) return true;
  }
  return false;
}

void EventQueue::setEventQueue(std::vector<int> t_eventQueue) {
  m_eventQueue = t_eventQueue;
}
const std::vector<int> &EventQueue::getMEventQueue() const {
  return m_eventQueue;
}
