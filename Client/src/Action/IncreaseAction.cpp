#include "IncreaseAction.hpp"

IncreaseAction::IncreaseAction(EntityID t_id, IncreaseType t_type, int t_value)
    : Action(ActionType::INCREASE, t_id) {
  m_increase_type = t_type;
  m_value = t_value;
}

IncreaseAction::IncreaseAction(EntityID t_id, IncreaseType t_type, int t_value,
                               int t_action_id)
    : Action(ActionType::INCREASE, t_id, t_action_id) {
  m_increase_type = t_type;
  m_value = t_value;
}
