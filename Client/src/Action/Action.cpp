#include "./Action.hpp"

Action::Action(ActionType type, EntityID id) : m_type(type), m_id(id) {
  m_action_id = action_counter++;
}

Action::Action(ActionType type, EntityID id, int t_action_id)
    : m_type(type), m_id(id) {
  m_action_id = t_action_id;
}

Action::~Action() {}

std::string Action::getTypeAsString() const {
  switch (m_type) {
    case ActionType::START:
      return "START";
    case ActionType::UP:
      return "UP";
    case ActionType::DOWN:
      return "DOWN";
    case ActionType::LEFT:
      return "LEFT";
    case ActionType::RIGHT:
      return "RIGHT";
    case ActionType::SHOOT:
      return "SHOOT";
    case ActionType::CREATE:
      return "CREATE";
    case ActionType::INCREASE:
      return "INCREASE";
    case ActionType::COLLISION:
      return "COLLISION";
    case ActionType::DEAD:
      return "DEAD";
    case ActionType::END:
      return "END";
    case ActionType::ERROR:
      return "ERROR";
  }
  return "ERROR";
}

std::string Action::getCommand() const {
  std::string type_string = getTypeAsString();
  std::string data = "";

  switch (m_type) {
    case ActionType::START:
    case ActionType::UP:
    case ActionType::DOWN:
    case ActionType::LEFT:
    case ActionType::RIGHT:
    case ActionType::DEAD:
    case ActionType::END:
      return std::to_string(m_action_id) + ";" + type_string + ";" +
             std::to_string(m_id) + ";";
    case ActionType::SHOOT:
      return std::to_string(m_action_id) + ";SHOOT;" + std::to_string(m_id) +
             ";" + std::to_string(m_damage) + ";" +
             std::to_string(m_shoot_type) + ";";
    case ActionType::INCREASE:
      return std::to_string(m_action_id) + ";INCREASE;" + std::to_string(m_id) +
             ";" + std::to_string(m_increase_type) + ";" +
             std::to_string(m_value) + ";";
    case ActionType::CREATE:
      data =
        std::to_string(m_position.x) + ";" + std::to_string(m_position.y) + ";";
      if (m_sprite_path.length() > 0) { data += m_sprite_path + ";"; }

      return std::to_string(m_action_id) + ";CREATE;" + std::to_string(m_id) +
             ";" + std::to_string(m_object_type) + ";" + data;
    case ActionType::COLLISION:
      return std::to_string(m_action_id) + ";COLLISION;" +
             std::to_string(m_id) + ";" +
             std::to_string(m_collision_partner_id) + ";";
  }
  return std::to_string(m_action_id) + ";" + type_string + ";" +
         std::to_string(m_id) + ";";
}

Action::ActionType Action::getType() const { return m_type; }
EntityID Action::getId() const { return m_id; }
