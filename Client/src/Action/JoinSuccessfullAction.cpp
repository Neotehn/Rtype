#include "./JoinSuccessfullAction.hpp"

JoinSuccessfullAction::JoinSuccessfullAction(EntityID t_id)
    : Action(ActionType::JOINSUCCESSFULL, t_id) {}

JoinSuccessfullAction::JoinSuccessfullAction(EntityID t_id, int action_id)
    : Action(ActionType::JOINSUCCESSFULL, action_id) {
  m_id = t_id;
}
