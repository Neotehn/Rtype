#include "ShootAction.hpp"

ShootAction::ShootAction(EntityID t_id, int t_damage, int t_type)
    : IAction(ActionType::SHOOT, t_id) {
  m_damage = t_damage;
  m_type = t_type;
}

ShootAction::ShootAction(EntityID t_id, int t_damage, int t_type,
                         int t_action_id)
    : IAction(ActionType::SHOOT, t_id, t_action_id) {
  m_damage = t_damage;
  m_type = t_type;
}

std::string ShootAction::getCommand() const {
  return std::to_string(m_action_id) + ";SHOOT;" + std::to_string(m_id) + ";" +
         std::to_string(m_damage) + ";" + std::to_string(m_type) + ";";
}

int ShootAction::getDamage() const { return m_damage; }

int ShootAction::getShootType() const { return m_type; }
