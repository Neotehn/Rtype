#include "MovementAction.hpp"

MovementAction::MovementAction(ActionType t_type, EntityID t_id)
    : Action(t_type, t_id) {}

MovementAction::MovementAction(ActionType t_type, EntityID t_id,
                               int t_action_id)
    : Action(t_type, t_id, t_action_id) {}
