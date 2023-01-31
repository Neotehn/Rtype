#ifndef CLIENT_SRC_EVENTQUEUE_HPP_
#define CLIENT_SRC_EVENTQUEUE_HPP_

#include <vector>

class EventQueue {
 public:
  EventQueue(std::vector<int> t_eventQueue);
  EventQueue();
  ~EventQueue();

  void setEventQueue(std::vector<int> t_eventQueue);
  bool checkIfKeyPressed(int t_key);

 private:
  std::vector<int> m_eventQueue;

 public:
  const std::vector<int> &getMEventQueue() const;
};

#endif  // CLIENT_SRC_EVENTQUEUE_HPP_
