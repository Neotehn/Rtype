#include "./IProtocol.hpp"

CreateAction IProtocol::getCreateAction(std::string command, int action_id,
                                        EntityID id) {
  std::string type =
    command.substr(command.find(';') + 3, command.find(';') + 4);
  float x =
    std::stof(command.substr(command.find(';') + 4, command.find(';') + 5));
  float y =
    std::stof(command.substr(command.find(';') + 5, command.find(';') + 6));
  std::string sprite_path;
  if (type == "PLAYER") {
    sprite_path = command.substr(command.find(';') + 6, command.find(';') + 7);
    return CreateAction(id, CreateAction::PLAYER, sf::Vector2f{x, y},
                        sprite_path, action_id);
  } else if (type == "ENEMY") {
    return CreateAction(id, CreateAction::ENEMY, sf::Vector2f{x, y}, "",
                        action_id);
  } else if (type == "BULLET") {
    return CreateAction(id, CreateAction::BULLET, sf::Vector2f{x, y}, "",
                        action_id);
  }
}

IncreaseAction IProtocol::getIncreaseAction(std::string command, int action_id,
                                            EntityID id) {
  std::string type =
    command.substr(command.find(';') + 3, command.find(';') + 4);
  int value =
    std::stoi(command.substr(command.find(';') + 4, command.find(';') + 5));
  if (type == "SPEED") {
    return IncreaseAction(id, IncreaseAction::SPEED, value, action_id);
  } else if (type == "FIRE_RATE") {
    return IncreaseAction(id, IncreaseAction::FIRE_RATE, value, action_id);
  } else if (type == "DAMAGE") {
    return IncreaseAction(id, IncreaseAction::DAMAGE, value, action_id);
  } else if (type == "LIFE") {
    return IncreaseAction(id, IncreaseAction::LIFE, value, action_id);
  } else if (type == "SHIELD") {
    return IncreaseAction(id, IncreaseAction::SHIELD, value, action_id);
  } else if (type == "BOMB") {
    return IncreaseAction(id, IncreaseAction::BOMB, value, action_id);
  }
}

IAction IProtocol::getAction(std::string command) {
  int action_id = std::stoi(command.substr(0, command.find(';')));
  std::string action_type =
    command.substr(command.find(';') + 1, command.find(';') + 2);
  EntityID id =
    std::stoi(command.substr(command.find(';') + 2, command.find(';') + 3));

  if (action_type == "START") {
    return StateAction(IAction::ActionType::START, id, action_id);
  } else if (action_type == "UP") {
    return MovementAction(IAction::ActionType::UP, id, action_id);
  } else if (action_type == "DOWN") {
    return MovementAction(IAction::ActionType::DOWN, id, action_id);
  } else if (action_type == "LEFT") {
    return MovementAction(IAction::ActionType::LEFT, id, action_id);
  } else if (action_type == "RIGHT") {
    return MovementAction(IAction::ActionType::RIGHT, id, action_id);
  } else if (action_type == "SHOOT") {
    int damage =
      std::stoi(command.substr(command.find(';') + 3, command.find(';') + 4));
    int type =
      std::stoi(command.substr(command.find(';') + 4, command.find(';') + 5));
    return ShootAction(id, damage, type, action_id);
  } else if (action_type == "CREATE") {
    return getCreateAction(command, action_id, id);
  } else if (action_type == "INCREASE") {
    return getIncreaseAction(command, action_id, id);
  } else if (action_type == "COLLISION") {
    EntityID id_other =
      std::stoi(command.substr(command.find(';') + 3, command.find(';') + 4));
    return CollisionAction(id, id_other, action_id);
  } else if (action_type == "DEAD") {
    return StateAction(IAction::ActionType::DEAD, id, action_id);
  } else if (action_type == "END") {
    return StateAction(IAction::ActionType::END, id, action_id);
  }
}
