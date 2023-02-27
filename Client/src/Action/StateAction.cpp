#include "StateAction.hpp"

StateAction::StateAction(ActionType t_type, EntityID t_id,
                         bool t_triggered_by_user)
    : Action(t_type, t_id) {
  m_triggered_by_user = t_triggered_by_user;
}

StateAction::StateAction(ActionType t_type, EntityID t_id, int t_action_id)
    : Action(t_type, t_id, t_action_id) {
  m_triggered_by_user = false;
}
