#include "StateAction.hpp"

StateAction::StateAction(ActionType t_type, EntityID t_id = 0)
    : IAction(t_type, t_id) {}

std::string StateAction::getCommand() const {
  std::string command;

  switch (m_type) {
    case ActionType::START:
      command = "START";
      break;
    case ActionType::DEAD:
      command = "DEAD";
      break;
    case ActionType::END:
      command = "END";
      break;
  }

  return std::to_string(m_action_id) + ";" + command + ";" +
         std::to_string(m_id);
}
