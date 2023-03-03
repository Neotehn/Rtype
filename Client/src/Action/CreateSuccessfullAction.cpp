#include "./CreateSuccessfullAction.hpp"

CreateSuccessfullAction::CreateSuccessfullAction(EntityID t_id)
    : Action(ActionType::CREATESUCCESSFULL, t_id) {}

CreateSuccessfullAction::CreateSuccessfullAction(EntityID t_id, int action_id)
    : Action(ActionType::CREATESUCCESSFULL, action_id) {
  m_id = t_id;
}
