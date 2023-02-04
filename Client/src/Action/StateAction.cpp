#include "StateAction.hpp"

StateAction::StateAction(ActionType t_type, EntityID t_id = 0)
    : Action(t_type, t_id) {}

StateAction::StateAction(ActionType t_type, EntityID t_id, int t_action_id)
    : Action(t_type, t_id, t_action_id) {}
