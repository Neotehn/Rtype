#include "CreateAction.hpp"

CreateAction::CreateAction(EntityID t_id, ObjectType t_object_type,
                           sf::Vector2f t_position, std::string t_sprite_path)
    : Action(ActionType::CREATE, t_id) {
  m_object_type = t_object_type;
  m_position = t_position;
  m_sprite_path = t_sprite_path;
}

CreateAction::CreateAction(EntityID t_id, ObjectType t_object_type,
                           sf::Vector2f t_position, std::string t_sprite_path,
                           int t_action_id)
    : Action(ActionType::CREATE, t_id, t_action_id) {
  m_object_type = t_object_type;
  m_position = t_position;
  m_sprite_path = t_sprite_path;
}
