#ifndef STATE_HPP_
#define STATE_HPP_

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

class StateMachine;

class State {
 public:
  State(StateMachine &t_machine, sf::RenderWindow &t_window,
        bool t_replace = true);

  virtual ~State() = default;

  State(const State &) = delete;
  State &operator=(const State &) = delete;

  virtual void update() = 0;
  virtual void draw() = 0;
  virtual void pause() = 0;
  virtual void resume() = 0;

  std::unique_ptr<State> next();

  const bool isReplacing();

 protected:
  StateMachine &m_state_machine;
  sf::RenderWindow &m_window;
  bool m_replace;
  std::unique_ptr<State> m_next;
};

#endif  // !STATE_HPP_
