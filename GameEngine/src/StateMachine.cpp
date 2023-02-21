#include "./StateMachine.hpp"

StateMachine::StateMachine() : m_resume(false), m_running(false) {}

void StateMachine::run(std::unique_ptr<State> t_state) {
  m_running = true;
  m_states.push(std::move(t_state));
}

const bool StateMachine::running() { return m_running; }

void StateMachine::draw() { m_states.top()->draw(); }

void StateMachine::nextState() {
  if (m_resume) {
    if (!m_states.empty()) { m_states.pop(); }
    if (!m_states.empty()) { m_states.top()->resume(); }
    m_resume = false;
  }
  if (!m_states.empty()) {
    std::unique_ptr<State> temp = m_states.top()->next();
    if (temp != nullptr) {
      if (temp->isReplacing()) {
        m_states.pop();
      } else {
        m_states.top()->pause();
      }
      m_states.push(std::move(temp));
    }
  }
}

void StateMachine::update() { m_states.top()->update(); }

void StateMachine::quit() { m_running = false; }

void StateMachine::lastState() { m_resume = true; }