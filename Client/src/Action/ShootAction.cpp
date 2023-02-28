#include "ShootAction.hpp"

ShootAction::ShootAction(EntityID t_id, int t_damage,
                         Action::ShootingType t_type, bool t_triggered_by_user)
    : Action(ActionType::SHOOT, t_id) {
  m_damage = t_damage;
  m_shoot_type = t_type;
  m_triggered_by_user = t_triggered_by_user;
}

ShootAction::ShootAction(EntityID t_id, int t_damage,
                         Action::ShootingType t_type, bool t_triggered_by_user,
                         int t_action_id)
    : Action(ActionType::SHOOT, t_id, t_action_id) {
  m_damage = t_damage;
  m_shoot_type = t_type;
  m_triggered_by_user = t_triggered_by_user;
}
