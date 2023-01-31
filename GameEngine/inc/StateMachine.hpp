#ifndef STATEMACHINE_HPP_
#define STATEMACHINE_HPP_

#include <iostream>
#include <memory>
#include <stack>
#include <stdexcept>

#include "State.hpp"

class StateMachine {
 public:
  StateMachine();
  const bool running() { return m_running; }
  void run(std::unique_ptr<State> t_state);
  void nextState();
  void update();
  void draw();
  void quit();
  void lastState();

  template<typename T>
  static std::unique_ptr<T> build(StateMachine &t_machine,
                                  sf::RenderWindow &t_window,
                                  bool t_replace = true);

 private:
  bool m_running;
  bool m_resume;
  std::stack<std::unique_ptr<State>> m_states;
};

template<typename T>
std::unique_ptr<T> StateMachine::build(StateMachine &t_machine,
                                       sf::RenderWindow &t_window,
                                       bool t_replace) {
  auto new_state = std::unique_ptr<T>{nullptr};

  try {
    new_state = std::make_unique<T>(t_machine, t_window, t_replace);
  } catch (std::runtime_error &exception) {
    std::cout << "Failed to create new State\n";
    std::cout << exception.what() << std::endl;
  }

  return new_state;
}

#endif  // !STATEMACHINE_HPP_
