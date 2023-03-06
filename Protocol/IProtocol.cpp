#include "./IProtocol.hpp"

std::shared_ptr<Action>
IProtocol::getCreateAction(std::vector<std::string> commands, int action_id,
                           EntityID id) {
  int type = std::stoi(commands[3]);
  float x = std::stof(commands[4]);
  float y = std::stof(commands[5]);
  std::string sprite_path;
  float velocity = 0;
  int player_id = 0;
  Action::ShootingType shooting_type;
  EntityID owner_id;
  float damage;
  if (type == Action::ObjectType::PLAYER) {
    sprite_path = commands[6];
    player_id = std::stoi(commands[7]);
    return std::make_shared<Action>(
      CreateAction(id, CreateAction::PLAYER, rtype::Vector2f{x, y}, sprite_path,
                   action_id, player_id, velocity));
  } else if (type == Action::ObjectType::ENEMY) {
    velocity = std::stof(commands[6]);
    return std::make_shared<Action>(CreateAction(
      id, CreateAction::ENEMY, rtype::Vector2f{x, y}, "", action_id, velocity));
  } else if (type == Action::ObjectType::PAYWALL) {
    return std::make_shared<Action>(CreateAction(
      id, CreateAction::PAYWALL, rtype::Vector2f{x, y}, "", action_id, 0));
  } else if (type == Action::ObjectType::ENDBOSS) {
    return std::make_shared<Action>(CreateAction(
      id, CreateAction::ENDBOSS, rtype::Vector2f{x, y}, "", action_id, 0));
  } else if (type == Action::ObjectType::BULLET) {
    shooting_type = Action::ShootingType(std::stoi(commands[6]));
    owner_id = std::stoull(commands[7]);
    damage = std::stof(commands[8]);
    return std::make_shared<Action>(
      CreateAction(id, CreateAction::BULLET, rtype::Vector2f{x, y}, owner_id,
                   damage, shooting_type));
  } else if (type == Action::ObjectType::EXPLOSION) {
    return std::make_shared<Action>(CreateAction(id, CreateAction::EXPLOSION,
                                                 rtype::Vector2f{x, y}, "",
                                                 action_id, velocity));
  } else if (type == Action::ObjectType::POWER_UP) {
    return std::make_shared<Action>(CreateAction(id, CreateAction::POWER_UP,
                                                 rtype::Vector2f{x, y}, "",
                                                 action_id, velocity));
  } else if (type == Action::ObjectType::ITEM) {
    velocity = std::stof(commands[6]);
    return std::make_shared<Action>(CreateAction(
      id, CreateAction::ITEM, rtype::Vector2f{x, y}, "", action_id, velocity));
  } else if (type == Action::ObjectType::OBSTACLE) {
    sprite_path = commands[6];
    player_id = std::stoi(commands[7]);  // actually total obstacle width
    return std::make_shared<Action>(CreateAction(id, CreateAction::OBSTACLE,
                                                 rtype::Vector2f{x, y},
                                                 player_id, sprite_path));
  } else {
    return std::make_shared<Action>(VoidAction(id, 0));
  }
}

std::shared_ptr<Action>
IProtocol::getIncreaseAction(std::vector<std::string> commands, int action_id,
                             EntityID id) {
  int type = std::stoi(commands[3]);
  int value = std::stoi(commands[4]);
  if (type == Action::IncreaseType::SPEED) {
    return std::make_shared<Action>(
      IncreaseAction(id, IncreaseAction::SPEED, value, action_id));
  } else if (type == Action::IncreaseType::FIRE_SHOT) {
    return std::make_shared<Action>(
      IncreaseAction(id, IncreaseAction::FIRE_SHOT, value, action_id));
  } else if (type == Action::IncreaseType::DAMAGE_I) {
    return std::make_shared<Action>(
      IncreaseAction(id, IncreaseAction::DAMAGE_I, value, action_id));
  } else if (type == Action::IncreaseType::LIFE) {
    return std::make_shared<Action>(
      IncreaseAction(id, IncreaseAction::LIFE, value, action_id));
  } else if (type == Action::IncreaseType::SHIELD) {
    return std::make_shared<Action>(
      IncreaseAction(id, IncreaseAction::SHIELD, value, action_id));
  } else if (type == Action::IncreaseType::BOMB_SHOT) {
    return std::make_shared<Action>(
      IncreaseAction(id, IncreaseAction::BOMB_SHOT, value, action_id));
  } else if (type == Action::IncreaseType::COINS) {
    return std::make_shared<Action>(
      IncreaseAction(id, IncreaseAction::COINS, value, action_id));
  } else if (type == Action::IncreaseType::KILLS) {
    return std::make_shared<Action>(
      IncreaseAction(id, IncreaseAction::KILLS, value, action_id));
  } else {
    return std::make_shared<Action>(VoidAction(id, 0));
  }
}

std::shared_ptr<Action> IProtocol::getAction(std::string command) {
  std::vector<std::string> commands;

  boost::split(commands, command, boost::is_any_of(";"));

  int action_id = std::stoi(commands[0]);
  std::string action_type = commands[1];
  EntityID id = std::stoull(commands[2]);

  if (action_type == "START") {
    std::string lobby_code = commands[3];
    int player_id = std::stoi(commands[4]);
    std::string player_name = commands[5];
    return std::make_shared<Action>(StateAction(Action::ActionType::START, id,
                                                action_id, lobby_code,
                                                player_id, player_name));
  } else if (action_type == "RESTART") {
    return std::make_shared<Action>(
      StateAction(Action::ActionType::RESTART, id, action_id));
  } else if (action_type == "UP") {
    return std::make_shared<Action>(
      MovementAction(Action::ActionType::UP, id, false, action_id));
  } else if (action_type == "DOWN") {
    return std::make_shared<Action>(
      MovementAction(Action::ActionType::DOWN, id, false, action_id));
  } else if (action_type == "LEFT") {
    return std::make_shared<Action>(
      MovementAction(Action::ActionType::LEFT, id, false, action_id));
  } else if (action_type == "RIGHT") {
    return std::make_shared<Action>(
      MovementAction(Action::ActionType::RIGHT, id, false, action_id));
  } else if (action_type == "POS") {
    rtype::Vector2f pos = {std::stof(commands[3]), std::stof(commands[4])};
    return std::make_shared<Action>(PosAction(id, pos, action_id));
  } else if (action_type == "SHOOT") {
    int damage = std::stoi(commands[4]);
    Action::ShootingType type = Action::ShootingType(std::stoi(commands[5]));
    return std::make_shared<Action>(
      ShootAction(id, damage, type, false, action_id));
  } else if (action_type == "CREATE") {
    return getCreateAction(commands, action_id, id);
  } else if (action_type == "INCREASE") {
    return getIncreaseAction(commands, action_id, id);
  } else if (action_type == "COLLISION") {
    EntityID id_other = std::stoull(commands[3]);
    return std::make_shared<Action>(CollisionAction(id, id_other, action_id));
  } else if (action_type == "DEAD") {
    return std::make_shared<Action>(
      StateAction(Action::ActionType::DEAD, id, action_id));
  } else if (action_type == "DESTROY") {
    return std::make_shared<Action>(DestroyAction(id, action_id));
  } else if (action_type == "DAMAGE") {
    int damage = std::stoi(commands[3]);
    EntityID player_id = std::stoull(commands[4]);
    return std::make_shared<Action>(
      DamageAction(id, damage, action_id, player_id));
  } else if (action_type == "ASKLEADERBOARD") {
    return std::make_shared<Action>(LeaderboardAction(id, action_id));
  } else if (action_type == "SENDLEADERBOARD") {
    std::vector<std::string> leaderboard;
    for (int i = 3; i < commands.size() - 1; i++) {
      leaderboard.push_back(commands[i]);
    }
    return std::make_shared<Action>(LeaderboardAction(id, leaderboard));
  } else if (action_type == "CREATELOBBY") {
    return std::make_shared<Action>(
      CreateLobbyAction(id, commands[3], commands[4], action_id));
  } else if (action_type == "JOINLOBBY") {
    return std::make_shared<Action>(
      JoinLobbyAction(id, commands[3], commands[4], action_id));
  } else if (action_type == "LEAVELOBBY") {
    return std::make_shared<Action>(
      LeaveLobbyAction(id, commands[3], commands[4], action_id));
  } else if (action_type == "JOINSUCCESSFULL") {
    std::vector<std::string> names;
    for (int i = 3; i < commands.size() - 1; i++) {
      names.push_back(commands[i]);
    }
    return std::make_shared<Action>(
      JoinSuccessfullAction(id, names, action_id));
  } else if (action_type == "CHAD") {
    return std::make_shared<Action>(
      ChadAction(id, commands[3], commands[4], action_id));
  } else if (action_type == "END") {
    return std::make_shared<Action>(
      StateAction(Action::ActionType::END, id, action_id));
  } else {
    return std::make_shared<Action>(VoidAction(id, 0));
  }
}
