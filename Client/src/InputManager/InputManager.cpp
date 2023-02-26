#include "InputManager.hpp"

#include <iostream>

InputManager::InputManager(int *t_level) {
  m_level = t_level;
  //SetExitKey(KEY_CAPS_LOCK);
}

// -4 = UP ; -3 = LEFT ; -2 = DOWN ; -1 = RIGHT
void InputManager::recordInputs(const rtype::Event &t_event) {
  switch (t_event.key) {
    case rtype::EventKey::W:
      m_input_queue.addToQueueIfNotExist(
        std::make_shared<Action>(
          MovementAction(Action::ActionType::UP, m_player_id, true)),
        Action::ActionType::UP);
      break;
    case rtype::EventKey::S:
      m_input_queue.addToQueueIfNotExist(
        std::make_shared<Action>(
          MovementAction(Action::ActionType::DOWN, m_player_id, true)),
        Action::ActionType::DOWN);
      break;
    case rtype::EventKey::D:
      m_input_queue.addToQueueIfNotExist(
        std::make_shared<Action>(
          MovementAction(Action::ActionType::RIGHT, m_player_id, true)),
        Action::ActionType::RIGHT);
      break;
    case rtype::EventKey::A:
      m_input_queue.addToQueueIfNotExist(
        std::make_shared<Action>(
          MovementAction(Action::ActionType::LEFT, m_player_id, true)),
        Action::ActionType::LEFT);
      break;
    case rtype::EventKey::Space:
      m_input_queue.addToQueueIfNotExist(
        std::make_shared<Action>(
          ShootAction(m_player_id, 1, Action::ShootingType::NORMAL, true)),
        Action::ActionType::SHOOT);
      break;
    case rtype::EventKey::M:
      m_input_queue.addToQueueIfNotExist(
        std::make_shared<Action>(
          ShootAction(m_player_id, 1, Action::ShootingType::BOMB, true)),
        Action::ActionType::SHOOT);
      break;
    case rtype::EventKey::N:
      m_input_queue.addToQueueIfNotExist(
        std::make_shared<Action>(
          ShootAction(m_player_id, 1, Action::ShootingType::FIRE, true)),
        Action::ActionType::SHOOT);
      break;
    case rtype::EventKey::U:
      m_input_queue.addToQueueIfNotExist(
        std::make_shared<Action>(
          StateAction(Action::ActionType::RESTART, *m_level + 1, true)),
        Action::ActionType::SHOOT);
      break;
    default:
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

EventQueue InputManager::getInputsWithoutPop() {
  EventQueue event_queue = m_input_queue;
  return event_queue;
}

bool InputManager::doesActionExist(std::shared_ptr<Action> t_action) {
  for (std::shared_ptr<Action> action : this->m_input_queue.getEventQueue()) {
    if (action->getActionId() == t_action->getActionId()) return true;
    if (action->getType() == t_action->getType()) return true;
  }
  return false;
}

bool InputManager::isPlayerIdSet() {
  if (m_player_id != 0) return true;
  return false;
}

void InputManager::setPlayerId(EntityID t_player_id) {
  m_player_id = t_player_id;
}

//sf::Vector2i InputManager::getMousePosition() {
//  return sf::Mouse::getPosition();
//}
//
//bool InputManager::isMouseLeftClicked() {
//  return sf::Mouse::isButtonPressed(sf::Mouse::Left);
//  // Needs click position
//}
//
//bool InputManager::isMouseRightClicked() {
//  return sf::Mouse::isButtonPressed(sf::Mouse::Right);
//  // Needs click position
//}