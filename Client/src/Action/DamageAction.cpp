#include "DamageAction.hpp"

DamageAction::DamageAction(EntityID t_id, int t_damage)
    : Action(ActionType::DAMAGE, t_id) {
  m_damage = t_damage;
}

DamageAction::DamageAction(EntityID t_id, int t_damgage, int t_action_id)
    : Action(ActionType::DAMAGE, t_action_id) {
  m_id = t_id;
  m_damage = t_damgage;
}
