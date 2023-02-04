#include "IncreaseAction.hpp"

IncreaseAction::IncreaseAction(EntityID t_id, IncreaseType t_type, int t_value)
    : IAction(ActionType::INCREASE, t_id) {
  m_type = t_type;
  m_value = t_value;
}

IncreaseAction::IncreaseAction(EntityID t_id, IncreaseType t_type, int t_value,
                               int t_action_id)
    : IAction(ActionType::INCREASE, t_id, t_action_id) {
  m_type = t_type;
  m_value = t_value;
}

std::string IncreaseAction::getCommand() const {
  return std::to_string(m_action_id) + ";INCREASE;" + std::to_string(m_id) +
         ";" + std::to_string(m_type) + ";" + std::to_string(m_value) + ";";
}

IncreaseAction::IncreaseType IncreaseAction::getIncreaseType() const {
  return m_type;
}

int IncreaseAction::getValue() const { return m_value; }
