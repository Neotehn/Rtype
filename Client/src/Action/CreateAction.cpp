#include "CreateAction.hpp"

CreateAction::CreateAction(EntityID t_id, ObjectType t_object_type,
                           rtype::Vector2f t_position,
                           std::string t_sprite_path)
    : Action(ActionType::CREATE, t_id) {
  m_object_type = t_object_type;
  m_position = t_position;
  m_sprite_path = t_sprite_path;
}

CreateAction::CreateAction(EntityID t_id, ObjectType t_object_type,
                           rtype::Vector2f t_position, EntityID t_owner_id,
                           float t_damage, std::string t_sprite_path)
    : Action(ActionType::CREATE, t_id) {
  m_object_type = t_object_type;
  m_position = t_position;
  m_sprite_path = t_sprite_path;
  m_collision_partner_id = t_owner_id;
  m_damage = t_damage;
}

CreateAction::CreateAction(EntityID t_id, ObjectType t_object_type,
                           rtype::Vector2f t_position,
                           std::string t_sprite_path, int t_client_id)
    : Action(ActionType::CREATE, t_id) {
  m_object_type = t_object_type;
  m_position = t_position;
  m_sprite_path = t_sprite_path;
  m_client_id = t_client_id;
}

CreateAction::CreateAction(EntityID t_id, ObjectType t_object_type,
                           rtype::Vector2f t_position,
                           std::string t_sprite_path, int t_action_id,
                           int t_client_id, float t_velocity)
    : Action(ActionType::CREATE, t_id, t_action_id) {
  m_object_type = t_object_type;
  m_position = t_position;
  m_sprite_path = t_sprite_path;
  m_velocity = t_velocity;
  m_client_id = t_client_id;
}

CreateAction::CreateAction(EntityID t_id, ObjectType t_object_type,
                           rtype::Vector2f t_position,
                           std::string t_sprite_path, int t_action_id,
                           float t_velocity)
    : Action(ActionType::CREATE, t_id, t_action_id) {
  m_object_type = t_object_type;
  m_position = t_position;
  m_sprite_path = t_sprite_path;
  if (t_object_type == ObjectType::ITEM) {
    m_item_type = int(t_velocity);
  } else {
    m_velocity = t_velocity;
  }
}

CreateAction::CreateAction(EntityID t_id, ObjectType t_object_type,
                           rtype::Vector2f t_position,
                           std::string t_sprite_path, float t_velocity)
    : Action(ActionType::CREATE, t_id) {
  m_object_type = t_object_type;
  m_position = t_position;
  m_sprite_path = t_sprite_path;
  m_velocity = t_velocity;
}

CreateAction::CreateAction(EntityID t_id, ObjectType t_object_type,
                           rtype::Vector2f t_position,
                           Action::ShootingType t_shooting_type)
    : Action(ActionType::CREATE, t_id) {
  m_object_type = t_object_type;
  m_position = t_position;
  m_shoot_type = t_shooting_type;
}

CreateAction::CreateAction(EntityID t_id, ObjectType t_object_type,
                           rtype::Vector2f t_position, EntityID t_owner_id,
                           float t_damage, Action::ShootingType t_shooting_type)
    : Action(ActionType::CREATE, t_id) {
  m_object_type = t_object_type;
  m_position = t_position;
  m_shoot_type = t_shooting_type;
  m_collision_partner_id = t_owner_id;
  m_damage = t_damage;
}

CreateAction::CreateAction(EntityID t_id, ObjectType t_object_type,
                           rtype::Vector2f t_position,
                           int t_total_obstacle_width,
                           std::string t_sprite_path)
    : Action(ActionType::CREATE, t_id) {
  m_object_type = t_object_type;
  m_position = t_position;
  m_sprite_path = t_sprite_path;
  m_total_obstacle_width = t_total_obstacle_width;
}