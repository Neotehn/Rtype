#include "MovementAction.hpp"

MovementAction::MovementAction(ActionType t_type, EntityID t_id)
    : IAction(t_type, t_id) {}

MovementAction::MovementAction(ActionType t_type, EntityID t_id,
                               int t_action_id)
    : IAction(t_type, t_id, t_action_id) {}

std::string MovementAction::getCommand() const {
  std::string command;

  switch (m_type) {
    case ActionType::UP:
      command = "UP";
      break;
    case ActionType::DOWN:
      command = "DOWN";
      break;
    case ActionType::LEFT:
      command = "LEFT";
      break;
    case ActionType::RIGHT:
      command = "RIGHT";
      break;
  }
  return std::to_string(m_action_id) + ";" + command + ";";
}