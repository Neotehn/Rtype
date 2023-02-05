#include "InputManager.hpp"

#include <iostream>

InputManager::InputManager() {
  //SetExitKey(KEY_CAPS_LOCK);
}

// -4 = UP ; -3 = LEFT ; -2 = DOWN ; -1 = RIGHT
void InputManager::recordInputs(const sf::Event &t_event) {
  // TODO: we need to link the events with the entity id from corresponding
  //  player
  switch (t_event.key.code) {
    case sf::Keyboard::W:
      m_input_queue.addToQueueIfNotExist(
        std::make_shared<Action>(
          MovementAction(Action::ActionType::UP, m_player_id, true)),
        Action::ActionType::UP);
      break;
    case sf::Keyboard::S:
      m_input_queue.addToQueueIfNotExist(
        std::make_shared<Action>(
          MovementAction(Action::ActionType::DOWN, m_player_id, true)),
        Action::ActionType::DOWN);
      break;
    case sf::Keyboard::D:
      m_input_queue.addToQueueIfNotExist(
        std::make_shared<Action>(
          MovementAction(Action::ActionType::RIGHT, m_player_id, true)),
        Action::ActionType::RIGHT);
      break;
    case sf::Keyboard::A:
      m_input_queue.addToQueueIfNotExist(
        std::make_shared<Action>(
          MovementAction(Action::ActionType::LEFT, m_player_id, true)),
        Action::ActionType::LEFT);
      break;
    case sf::Keyboard::Space:
      m_input_queue.addToQueueIfNotExist(
        std::make_shared<Action>(ShootAction(m_player_id, 1, 1, true)),
        Action::ActionType::SHOOT);
      break;
  }

  //std::this_thread::sleep_for(std::chrono::milliseconds(100)); // This should change
}

void InputManager::addActionsToQueue(std::shared_ptr<Action> t_action) {
  this->m_input_queue.addToQueue(t_action);
}

void InputManager::popInputs() {
  if (!m_input_queue.empty()) this->m_input_queue.clear();
}

EventQueue InputManager::getInputs() {
  EventQueue event_queue = m_input_queue;
  this->popInputs();
  return event_queue;
}

sf::Vector2i InputManager::getMousePosition() {
  return sf::Mouse::getPosition();
}

bool InputManager::doesActionExist(std::shared_ptr<Action> t_action) {
  for (std::shared_ptr<Action> action : this->m_input_queue.getEventQueue()) {
    if (action->getActionId() == t_action->getActionId()) return true;
    if (action->getType() == t_action->getType()) return true;
  }
  return false;
}

bool InputManager::isMouseLeftClicked() {
  return sf::Mouse::isButtonPressed(sf::Mouse::Left);
  // Needs click position
}

bool InputManager::isMouseRightClicked() {
  return sf::Mouse::isButtonPressed(sf::Mouse::Right);
  // Needs click position
}