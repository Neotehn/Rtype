#include "CollisionAction.hpp"

CollisionAction::CollisionAction(EntityID t_id, EntityID t_other_id)
    : IAction(ActionType::COLLISION, t_id) {
  m_collision_partner_id = t_other_id;
}

CollisionAction::CollisionAction(EntityID t_id, EntityID t_other_id,
                                 int t_action_id)
    : IAction(ActionType::COLLISION, t_id, t_action_id) {
  m_collision_partner_id = t_other_id;
}

std::string CollisionAction::getCommand() const {
  return std::to_string(m_action_id) + ";COLLISION;" + std::to_string(m_id) +
         ";" + std::to_string(m_collision_partner_id) + ";";
}

EntityID CollisionAction::getCollisionPartnerId() const {
  return m_collision_partner_id;
}