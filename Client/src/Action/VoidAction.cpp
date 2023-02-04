#include "VoidAction.hpp"

VoidAction::VoidAction(EntityID t_id, int t_action_id)
    : IAction(ActionType::ERROR, t_id, t_action_id) {}

std::string VoidAction::getCommand() const { return ";;;"; }
