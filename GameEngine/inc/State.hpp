/*
** EPITECH PROJECT, 2023
** StateMachine
** File description:
** State
*/

#ifndef STATE_HPP_
#define STATE_HPP_

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

class StateMachine;

class State {
 public:
  State(StateMachine &machine, sf::RenderWindow &window, bool replace = true);

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

#endif /* !STATE_HPP_ */
