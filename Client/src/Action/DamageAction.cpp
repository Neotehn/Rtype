#include "DamageAction.hpp"

DamageAction::DamageAction(EntityID t_id, int t_damage, EntityID t_player_id)
    : Action(ActionType::DAMAGE, t_id) {
  m_damage = t_damage;
  m_collision_partner_id = t_player_id;
}

DamageAction::DamageAction(EntityID t_id, int t_damgage, int t_action_id,
                           EntityID t_player_id)
    : Action(ActionType::DAMAGE, t_action_id) {
  m_id = t_id;
  m_damage = t_damgage;
  m_collision_partner_id = t_player_id;
}
