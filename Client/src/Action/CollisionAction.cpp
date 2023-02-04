#include "CollisionAction.hpp"

CollisionAction::CollisionAction(EntityID t_id, EntityID t_other_id)
    : Action(ActionType::COLLISION, t_id) {
  m_collision_partner_id = t_other_id;
}

CollisionAction::CollisionAction(EntityID t_id, EntityID t_other_id,
                                 int t_action_id)
    : Action(ActionType::COLLISION, t_id, t_action_id) {
  m_collision_partner_id = t_other_id;
}
