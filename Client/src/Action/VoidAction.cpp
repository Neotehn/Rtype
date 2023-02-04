#include "VoidAction.hpp"

VoidAction::VoidAction(EntityID t_id, int t_action_id)
    : Action(ActionType::ERROR, t_id, t_action_id) {}
