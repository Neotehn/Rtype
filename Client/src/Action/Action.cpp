#include "./Action.hpp"
#include <iostream>

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
    case ActionType::RESTART:
      return "RESTART";
    case ActionType::UP:
      return "UP";
    case ActionType::DOWN:
      return "DOWN";
    case ActionType::LEFT:
      return "LEFT";
    case ActionType::RIGHT:
      return "RIGHT";
    case ActionType::POS:
      return "POS";
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
    case ActionType::DESTROY:
      return "DESTROY";
    case ActionType::DAMAGE:
      return "DAMAGE";
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
      return std::to_string(m_action_id) + ";" + type_string + ";" +
             std::to_string(m_id) + ";" + std::to_string(m_client_id) + ";";
    case ActionType::DEAD:
    case ActionType::END:
      return std::to_string(m_action_id) + ";" + type_string + ";" +
             std::to_string(m_id) + ";";
    case ActionType::UP:
    case ActionType::DOWN:
    case ActionType::LEFT:
    case ActionType::RIGHT:
    case ActionType::RESTART:
      return std::to_string(m_action_id) + ";" + type_string + ";" +
             std::to_string(m_id) + ";" + std::to_string(m_triggered_by_user) +
             ";";
    case ActionType::POS:
      return std::to_string(m_action_id) + ";" + type_string + ";" +
             std::to_string(m_id) + ";" + std::to_string(m_position.x) + ";" +
             std::to_string(m_position.y) + ";";
    case ActionType::SHOOT:
      return std::to_string(m_action_id) + ";SHOOT;" + std::to_string(m_id) +
             ";" + std::to_string(m_triggered_by_user) + ";" +
             std::to_string(m_damage) + ";" + std::to_string(m_shoot_type) +
             ";";
    case ActionType::INCREASE:
      return std::to_string(m_action_id) + ";INCREASE;" + std::to_string(m_id) +
             ";" + std::to_string(m_increase_type) + ";" +
             std::to_string(m_value) + ";";
    case ActionType::DAMAGE:
      return std::to_string(m_action_id) + ";DAMAGE;" + std::to_string(m_id) +
             ";" + std::to_string(m_damage) + ";" +
             std::to_string(m_collision_partner_id) + ";";
    case ActionType::CREATE:
      data =
        std::to_string(m_position.x) + ";" + std::to_string(m_position.y) + ";";
      if (m_sprite_path.length() > 0) { data += m_sprite_path + ";"; }
      if (m_velocity >= -1) { data += std::to_string(m_velocity) + ";"; }
      if (m_item_type != 0) {
        data += std::to_string(float(m_item_type)) + ";";
      }
      if (m_client_id != 0) { data += std::to_string(m_client_id) + ";"; }
      if (m_collision_partner_id != 0) {
        data += std::to_string(m_collision_partner_id) + ";";
      }
      if (m_damage != 0) { data += std::to_string(m_damage) + ";"; }
      std::cout << std::to_string(m_velocity) << std::endl;

      return std::to_string(m_action_id) + ";CREATE;" + std::to_string(m_id) +
             ";" + std::to_string(m_object_type) + ";" + data;
    case ActionType::COLLISION:
      return std::to_string(m_action_id) + ";COLLISION;" +
             std::to_string(m_id) + ";" +
             std::to_string(m_collision_partner_id) + ";";
    case ActionType::DESTROY:
      return std::to_string(m_action_id) + ";DESTROY;" + std::to_string(m_id) +
             ";";
  }
  return std::to_string(m_action_id) + ";" + type_string + ";" +
         std::to_string(m_id) + ";";
}

int Action::getActionId() const { return m_action_id; }
Action::ActionType Action::getType() const { return m_type; }
EntityID Action::getId() const { return m_id; }

bool Action::isTriggeredByUser() const { return m_triggered_by_user; }

EntityID Action::getCollisionPartnerId() const {
  return m_collision_partner_id;
}

Action::ObjectType Action::getCreateType() const { return m_object_type; }

rtype::Vector2f Action::getCreatePosition() const { return m_position; }

std::string Action::getCreateSpritePath() const { return m_sprite_path; }

Action::IncreaseType Action::getIncreaseType() const { return m_increase_type; }

int Action::getIncreaseValue() const { return m_value; }

int Action::getShootDamage() const { return m_damage; }

Action::ShootingType Action::getShootType() const { return m_shoot_type; }

float Action::getVelocity() const { return m_velocity; }

int Action::getItemType() const { return m_item_type; }

void Action::setPlayerId(EntityID t_id) { m_id = t_id; }

int Action::getClientId() const { return m_client_id; }

void Action::setClientId(int t_client_id) { m_client_id = t_client_id; }
