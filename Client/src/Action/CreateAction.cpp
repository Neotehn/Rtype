#include "CreateAction.hpp"

CreateAction::CreateAction(EntityID t_id, ObjectType t_object_type,
sf::Vector2f t_position, std::string t_sprite_path) : IAction
(ActionType::CREATE, t_id) {
  m_object_type = t_object_type;
  m_position = t_position;
  m_sprite_path = t_sprite_path;
}

std::string CreateAction::getCommand() const {
  std::string data = std::to_string(m_position.x) + ";" +
    std::to_string(m_position.y) + ";";
  if (m_sprite_path.length() > 0) {
    data += m_sprite_path + ";";
  }

  return std::to_string(m_action_id) + ";CREATE;" + std::to_string(m_id) + ";"
   + std::to_string(m_object_type) + ";" + data;
}

CreateAction::ObjectType CreateAction::getObjectType() const {
  return m_object_type;
}

sf::Vector2f CreateAction::getPosition() const {
  return m_position;
}

std::string CreateAction::getSpritePath() const {
  return m_sprite_path;
}
