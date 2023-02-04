#include "ShootAction.hpp"

ShootAction::ShootAction(EntityID t_id, int t_damage, int t_type)
    : Action(ActionType::SHOOT, t_id) {
  m_damage = t_damage;
  m_shoot_type = t_type;
}

ShootAction::ShootAction(EntityID t_id, int t_damage, int t_type,
                         int t_action_id)
    : Action(ActionType::SHOOT, t_id, t_action_id) {
  m_damage = t_damage;
  m_shoot_type = t_type;
}
