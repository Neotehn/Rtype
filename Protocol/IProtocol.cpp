#include "./IProtocol.hpp"

std::shared_ptr<IAction>
IProtocol::getCreateAction(std::vector<std::string> commands, int action_id,
                           EntityID id) {
  std::string type = commands[3];
  float x = std::stof(commands[4]);
  float y = std::stof(commands[5]);
  std::string sprite_path;
  if (type == "PLAYER") {
    sprite_path = commands[6];
    return std::make_shared<IAction>(CreateAction(
      id, CreateAction::PLAYER, sf::Vector2f{x, y}, sprite_path, action_id));
  } else if (type == "ENEMY") {
    return std::make_shared<IAction>(
      CreateAction(id, CreateAction::ENEMY, sf::Vector2f{x, y}, "", action_id));
  } else if (type == "BULLET") {
    return std::make_shared<IAction>(CreateAction(
      id, CreateAction::BULLET, sf::Vector2f{x, y}, "", action_id));
  } else {
    return std::make_shared<IAction>(VoidAction(id, 0));
  }
}

std::shared_ptr<IAction>
IProtocol::getIncreaseAction(std::vector<std::string> commands, int action_id,
                             EntityID id) {
  std::string type = commands[3];
  int value = std::stoi(commands[4]);
  if (type == "SPEED") {
    return std::make_shared<IAction>(
      IncreaseAction(id, IncreaseAction::SPEED, value, action_id));
  } else if (type == "FIRE_RATE") {
    return std::make_shared<IAction>(
      IncreaseAction(id, IncreaseAction::FIRE_RATE, value, action_id));
  } else if (type == "DAMAGE") {
    return std::make_shared<IAction>(
      IncreaseAction(id, IncreaseAction::DAMAGE, value, action_id));
  } else if (type == "LIFE") {
    return std::make_shared<IAction>(
      IncreaseAction(id, IncreaseAction::LIFE, value, action_id));
  } else if (type == "SHIELD") {
    return std::make_shared<IAction>(
      IncreaseAction(id, IncreaseAction::SHIELD, value, action_id));
  } else if (type == "BOMB") {
    return std::make_shared<IAction>(
      IncreaseAction(id, IncreaseAction::BOMB, value, action_id));
  } else {
    return std::make_shared<IAction>(VoidAction(id, 0));
  }
}

std::shared_ptr<IAction> IProtocol::getAction(std::string command) {
  std::vector<std::string> commands;

  boost::split(commands, command, boost::is_any_of(";"));

  int action_id = std::stoi(commands[0]);
  std::string action_type = commands[1];
  EntityID id = std::stoi(commands[2]);

  if (action_type == "START") {
    return std::make_shared<IAction>(
      StateAction(IAction::ActionType::START, id, action_id));
  } else if (action_type == "UP") {
    return std::make_shared<IAction>(
      MovementAction(IAction::ActionType::UP, id, action_id));
  } else if (action_type == "DOWN") {
    return std::make_shared<IAction>(
      MovementAction(IAction::ActionType::DOWN, id, action_id));
  } else if (action_type == "LEFT") {
    return std::make_shared<IAction>(
      MovementAction(IAction::ActionType::LEFT, id, action_id));
  } else if (action_type == "RIGHT") {
    return std::make_shared<IAction>(
      MovementAction(IAction::ActionType::RIGHT, id, action_id));
  } else if (action_type == "SHOOT") {
    int damage = std::stoi(commands[3]);
    int type = std::stoi(commands[4]);
    return std::make_shared<IAction>(ShootAction(id, damage, type, action_id));
  } else if (action_type == "CREATE") {
    return getCreateAction(commands, action_id, id);
  } else if (action_type == "INCREASE") {
    return getIncreaseAction(commands, action_id, id);
  } else if (action_type == "COLLISION") {
    EntityID id_other = std::stoi(commands[3]);
    return std::make_shared<IAction>(CollisionAction(id, id_other, action_id));
  } else if (action_type == "DEAD") {
    return std::make_shared<IAction>(
      StateAction(IAction::ActionType::DEAD, id, action_id));
  } else if (action_type == "END") {
    return std::make_shared<IAction>(
      StateAction(IAction::ActionType::END, id, action_id));
  } else {
    return std::make_shared<IAction>(VoidAction(id, 0));
  }
}
