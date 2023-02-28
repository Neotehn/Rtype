#include "DestroyAction.hpp"

DestroyAction::DestroyAction(EntityID t_id)
    : Action(ActionType::DESTROY, t_id) {}

DestroyAction::DestroyAction(EntityID t_id, int t_action_id)
    : Action(ActionType::DESTROY, t_action_id) {
  m_id = t_id;
}
