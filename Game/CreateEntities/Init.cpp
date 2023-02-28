#include "Init.hpp"
#include <string>
#include <vector>

AssetLoader assetLoader;
int level = 1;
std::vector<EntityID> background_entities;

bool loadLevel(int *t_level, std::shared_ptr<EntityManager> t_em,
               rtype::IGraphicLoader *t_graphic_loader, rtype::IMusic *t_music,
               bool t_play_music) {
  for (EntityID ent : EntityViewer<Bullet>(*t_em.get())) {
    t_em->destroyEntity(ent);
  }
  for (EntityID ent : EntityViewer<AnimationObj>(*t_em.get())) {
    t_em->destroyEntity(ent);
  }
  for (EntityID ent : EntityViewer<SpinningItem>(*t_em.get())) {
    t_em->destroyEntity(ent);
  }

  if (!assetLoader.loadLevel(*t_level)) {
    if (*t_level != 1) {
      *t_level = 1;
      level = 1;
      loadLevel(t_level, t_em, t_graphic_loader, t_music);
    }
    return false;
  }

  for (EntityID ent : EntityViewer<Player>(*t_em.get())) {
    Player *player = (*t_em.get()).Get<Player>(ent);
    player->damage_factor += 0.3;
    player->speed += 0.2;
    player->exp += 10 * player->kills;
    player->kills = 0;
  }

  level = *t_level;
  t_music->stop();
  loadMusic(t_music, t_play_music);
  initBackground(t_em, t_graphic_loader);
  return true;
}

EntityID initPlayer(std::shared_ptr<EntityManager> t_entity_manager,
                    UdpServer *t_serverCom,
                    rtype::IGraphicLoader *t_graphic_loader) {
  EntityID player = t_entity_manager->createNewEntity();

  SpriteECS player_sprite =
    SpriteECS("../Client/sprites/starship.png", t_graphic_loader);

  Pos player_pos = Pos{rtype::Vector2f{0.0, 0.0}, rtype::Vector2f{300, 300}};

  rtype::IRectangleShape *body = t_graphic_loader->loadRectangleShape();
  body->setSize({200, 200});
  body->setPosition({player_pos.position.x, player_pos.position.y});
  body->setTexture(player_sprite.getTexture());
  body->setRotation(90.0);

  Health health = initPlayerHealthBar(t_graphic_loader);
  Player player_obj =
    Player{player_sprite, player_pos, body,
           health,        10,         t_serverCom->getPlayerIdCount()};
  t_serverCom->setPlayerIdCount(t_serverCom->getPlayerIdCount() + 1);
  t_entity_manager->Assign<Player>(player, player_obj);
  t_serverCom->addEvent(std::make_shared<Action>(CreateAction(
    player, Action::ObjectType::PLAYER, player_pos.position,
    "../Client/sprites/starship.png", t_serverCom->getPlayerIdCount())));
  return player;
}

void initPlayerClient(EntityID t_id, std::string t_sprite_path,
                      rtype::Vector2f t_pos,
                      std::shared_ptr<EntityManager> t_entity_manager,
                      rtype::IGraphicLoader *t_graphic_loader) {
  EntityID player = t_entity_manager->createNewEntity(t_id);
  SpriteECS player_sprite = SpriteECS(t_sprite_path, t_graphic_loader);

  Pos player_pos = Pos{rtype::Vector2f{0, 0}, t_pos};

  rtype::IRectangleShape *body = t_graphic_loader->loadRectangleShape();
  body->setSize({200, 200});
  body->setPosition({player_pos.position.x, player_pos.position.y});
  body->setTexture(player_sprite.getTexture());
  body->setRotation(90.0);

  Health health = initPlayerHealthBar(t_graphic_loader);
  Player player_obj = Player{player_sprite, player_pos, body, health, 10};
  t_entity_manager->Assign<Player>(player, player_obj);
}

Health initPlayerHealthBar(rtype::IGraphicLoader *t_graphic_loader) {
  SpriteECS player_health_bar_sprite_full =
    SpriteECS("../Client/sprites/playerassets/Fulllife.png", t_graphic_loader);

  Pos bar_pos = Pos{rtype::Vector2f{0, 0}, rtype::Vector2f{120, 230}};

  HealthBar bar_stats =
    HealthBar{std::vector<std::string>{
                std::string("../Client/sprites/playerassets/ouch 3x.png"),
                std::string("../Client/sprites/playerassets/ouch 2x.png"),
                std::string("../Client/sprites/playerassets/ouch.png"),
                std::string("../Client/sprites/playerassets/Fulllife.png")},
              3};

  rtype::IRectangleShape *body = t_graphic_loader->loadRectangleShape();
  body->setSize({126, 42});
  body->setPosition({bar_pos.position.x, bar_pos.position.y});
  body->setTexture(player_health_bar_sprite_full.getTexture());

  return Health{bar_stats, bar_pos, body};
}

void initBulletClient(EntityID t_id, rtype::Vector2f t_pos,
                      Action::ShootingType t_shooting_type,
                      std::shared_ptr<EntityManager> t_em,
                      rtype::IGraphicLoader *t_graphic_loader,
                      EntityID t_owner_id) {
  EntityID bullet = t_em->createNewEntity(t_id);

  rtype::IRectangleShape *bullet_body = t_graphic_loader->loadRectangleShape();
  bullet_body->setSize({20, 20});
  bullet_body->setPosition({t_pos.x, t_pos.y});

  switch (t_shooting_type) {
    case Action::ShootingType::NORMAL:
      bullet_body->setTexture(
        SpriteECS("./../Client/sprites/shoot2.png", t_graphic_loader)
          .getTexture());
      break;
    case Action::ShootingType::FIRE:
      bullet_body->setTexture(
        SpriteECS("./../Client/sprites/shoot3.png", t_graphic_loader)
          .getTexture());
      break;
    case Action::ShootingType::BOMB:
      bullet_body->setTexture(
        SpriteECS("./../Client/sprites/shoot4.png", t_graphic_loader)
          .getTexture());
      break;
  }
  std::cout << "create bullet for player " << std::to_string(t_owner_id)
            << std::endl;
  Bullet displayable_bullet = Bullet{bullet_body, 10.0, t_pos, t_owner_id};
  t_em->Assign<Bullet>(bullet, displayable_bullet);
}

void initEnemy(std::shared_ptr<EntityManager> t_em,
               rtype::IGraphicLoader *t_graphic_loader,
               UdpServer *t_server_com) {
  Json::Value enemy_data = assetLoader.getEnemyData()[0];
  int size = enemy_data["size"].asInt();
  EntityID enemy = t_em->createNewEntity();
  SpriteECS sprite = SpriteECS(enemy_data["path"].asString(), t_graphic_loader);
  rtype::Vector2f enemy_pos = {800, float(rand() % 600 + 100)};
  float velocity_direction = float(rand() % 3 - 1);

  rtype::IRectangleShape *body = t_graphic_loader->loadRectangleShape();
  body->setSize({30, 30});
  body->setPosition({enemy_pos.x, enemy_pos.y});
  body->setTexture(sprite.getTexture());
  body->setFillColor(
    rtype::Color{static_cast<unsigned char>(enemy_data["color"]["r"].asInt()),
                 static_cast<unsigned char>(enemy_data["color"]["g"].asInt()),
                 static_cast<unsigned char>(enemy_data["color"]["b"].asInt()),
                 static_cast<unsigned char>(enemy_data["color"]["a"].asInt())});
  body->setTextureRect(rtype::IntRect{0, 0, size, size});

  AnimationObj enemy_obj = AnimationObj{
    "enemy", Pos{{-7, velocity_direction}, enemy_pos},
    AnimationTime{.current_animation_time = 0,
                  .display_time = 1,
                  .last_timer = 0},
    AnimationRect{.size = size, .limit = enemy_data["limit"].asInt()}, body};
  t_em->Assign<AnimationObj>(enemy, enemy_obj);
  t_server_com->addEvent(std::make_shared<Action>(CreateAction(
    enemy, Action::ObjectType::ENEMY, enemy_pos, "", velocity_direction)));
}

void initEnemyClient(EntityID t_id, rtype::Vector2f t_pos, float t_velocity,
                     std::shared_ptr<EntityManager> t_em,
                     rtype::IGraphicLoader *t_graphic_loader) {
  Json::Value enemy_data = assetLoader.getEnemyData()[0];
  int size = enemy_data["size"].asInt();
  EntityID enemy = t_em->createNewEntity(t_id);
  SpriteECS sprite = SpriteECS(enemy_data["path"].asString(), t_graphic_loader);
  rtype::IRectangleShape *body = t_graphic_loader->loadRectangleShape();
  body->setSize({30, 30});
  body->setPosition({t_pos.x, t_pos.y});
  body->setTexture(sprite.getTexture());
  body->setTextureRect(rtype::IntRect{0, 0, size, size});
  body->setFillColor(
    rtype::Color{static_cast<unsigned char>(enemy_data["color"]["r"].asInt()),
                 static_cast<unsigned char>(enemy_data["color"]["g"].asInt()),
                 static_cast<unsigned char>(enemy_data["color"]["b"].asInt()),
                 static_cast<unsigned char>(enemy_data["color"]["a"].asInt())});

  AnimationObj enemy_obj = AnimationObj{
    "enemy", Pos{{-7, t_velocity}, t_pos},
    AnimationTime{.current_animation_time = 0,
                  .display_time = 0.1,
                  .last_timer = 0},
    AnimationRect{.size = size, .limit = enemy_data["limit"].asInt()}, body};
  t_em->Assign<AnimationObj>(enemy, enemy_obj);
}

void initExplosionClient(EntityID t_id, rtype::Vector2f t_pos,
                         std::shared_ptr<EntityManager> t_em,
                         rtype::IGraphicLoader *t_graphic_loader) {
  EntityID explosion = t_em->createNewEntity(t_id);
  SpriteECS sprite =
    SpriteECS("./../Client/sprites/explosion/Explosion.png", t_graphic_loader);
  rtype::IRectangleShape *body = t_graphic_loader->loadRectangleShape();
  body->setSize({50, 50});
  body->setPosition({t_pos.x, t_pos.y});
  body->setTexture(sprite.getTexture());
  body->setTextureRect(rtype::IntRect{0, 0, 96, 96});

  AnimationObj explosion_obj =
    AnimationObj{"explosion", Pos{{0, 0}, t_pos},
                 AnimationTime{.current_animation_time = 0,
                               .display_time = 0.06,
                               .last_timer = 0},
                 AnimationRect{.size = 96, .limit = 1056}, body};
  t_em->Assign<AnimationObj>(explosion, explosion_obj);
}

void createCoin(std::shared_ptr<EntityManager> t_em,
                rtype::IGraphicLoader *t_graphic_loader,
                UdpServer *t_server_com) {
  EntityID powerup = t_em->createNewEntity();
  SpriteECS sprite =
    SpriteECS("./../Client/sprites/powerup/coin.png", t_graphic_loader);
  rtype::Vector2f powerup_pos = {800, float(rand() % 600 + 100)};

  rtype::IRectangleShape *body = t_graphic_loader->loadRectangleShape();
  body->setSize({30, 30});
  body->setPosition({powerup_pos.x, powerup_pos.y});
  body->setTexture(sprite.getTexture());
  body->setTextureRect(rtype::IntRect{0, 0, 84, 84});

  AnimationObj powerup_obj =
    AnimationObj{"powerup", Pos{{-7, 0}, powerup_pos},
                 AnimationTime{.current_animation_time = 0,
                               .display_time = 0.1,
                               .last_timer = 0},
                 AnimationRect{.size = 84, .limit = 420}, body};
  t_em->Assign<AnimationObj>(powerup, powerup_obj);

  t_server_com->addEvent(std::make_shared<Action>(
    CreateAction(powerup, Action::ObjectType::POWER_UP, powerup_pos, "", 0)));
}

void createItem(std::string t_path, rtype::ItemType t_type, int t_value,
                std::shared_ptr<EntityManager> t_em,
                rtype::IGraphicLoader *t_graphic_loader,
                UdpServer *t_serverCom) {
  EntityID powerup = t_em->createNewEntity();
  SpriteECS sprite = SpriteECS(t_path, t_graphic_loader);
  rtype::Vector2f powerup_pos = {800, float(rand() % 600 + 100)};

  rtype::IRectangleShape *body = t_graphic_loader->loadRectangleShape();
  body->setSize({30, 30});
  body->setPosition({powerup_pos.x, powerup_pos.y});
  body->setTexture(sprite.getTexture());
  body->setTextureRect(rtype::IntRect{0, 0, 84, 84});

  SpinningItem item_obj = {t_type,
                           t_value,
                           sprite,
                           Pos{{-7, 0}, powerup_pos},
                           AnimationTime{.current_animation_time = 0,
                                         .display_time = 0.1,
                                         .last_timer = 0},
                           body};
  t_em->Assign<SpinningItem>(powerup, item_obj);

  t_serverCom->addEvent(std::make_shared<Action>(
    CreateAction(powerup, Action::ObjectType::ITEM, powerup_pos, "", t_type)));
}

void initPowerUp(std::shared_ptr<EntityManager> t_em,
                 rtype::IGraphicLoader *t_graphic_loader,
                 UdpServer *t_server_com) {
  int random_powerup = rand() % 5;
  if (random_powerup == 0) {
    createCoin(t_em, t_graphic_loader, t_server_com);
  } else if (random_powerup == 1) {
    createItem("../Client/sprites/powerup/life_item.png",
               rtype::ItemType::LIFE_ITEM, 1, t_em, t_graphic_loader,
               t_server_com);
  } else if (random_powerup == 2) {
    createItem("../Client/sprites/powerup/speed_item.png",
               rtype::ItemType::SPEED_ITEM, 3, t_em, t_graphic_loader,
               t_server_com);
  } else if (random_powerup == 3) {
    createItem("../Client/sprites/powerup/bomb_item.png",
               rtype::ItemType::BOMB_ITEM, 5, t_em, t_graphic_loader,
               t_server_com);
  } else {
    createItem("../Client/sprites/powerup/fire_item.png",
               rtype::ItemType::FIRE_ITEM, 5, t_em, t_graphic_loader,
               t_server_com);
  }
}

void initPowerUpClient(EntityID t_id, rtype::Vector2f t_pos,
                       std::shared_ptr<EntityManager> t_em,
                       rtype::IGraphicLoader *t_graphic_loader) {
  EntityID powerup = t_em->createNewEntity(t_id);
  SpriteECS sprite =
    SpriteECS("./../Client/sprites/powerup/coin.png", t_graphic_loader);
  rtype::IRectangleShape *body = t_graphic_loader->loadRectangleShape();
  body->setSize({30, 30});
  body->setPosition({t_pos.x, t_pos.y});
  body->setTexture(sprite.getTexture());
  body->setTextureRect(rtype::IntRect{0, 0, 84, 84});

  AnimationObj power_up =
    AnimationObj{"powerup", Pos{{-7, 0}, t_pos},
                 AnimationTime{.current_animation_time = 0,
                               .display_time = 0.1,
                               .last_timer = 0},
                 AnimationRect{.size = 84, .limit = 420}, body};
  t_em->Assign<AnimationObj>(powerup, power_up);
}

void initItemClient(EntityID t_id, rtype::ItemType t_item_type,
                    rtype::Vector2f t_pos, std::shared_ptr<EntityManager> t_em,
                    rtype::IGraphicLoader *t_graphic_loader) {
  std::string path = "";
  int value = 0;
  switch (t_item_type) {
    case rtype::LIFE_ITEM:
      path = "../Client/sprites/powerup/life_item.png";
      value = 1;
      break;
    case rtype::SPEED_ITEM:
      path = "../Client/sprites/powerup/speed_item.png";
      value = 3;
      break;
    case rtype::BOMB_ITEM:
      path = "../Client/sprites/powerup/bomb_item.png";
      value = 5;
      break;
    case rtype::FIRE_ITEM:
      path = "../Client/sprites/powerup/fire_item.png";
      value = 5;
      break;
    default:
      break;
  }
  EntityID item = t_em->createNewEntity(t_id);
  SpriteECS item_sprite = SpriteECS(path, t_graphic_loader);

  Pos player_pos = Pos{rtype::Vector2f{-7, 0}, t_pos};

  rtype::IRectangleShape *body = t_graphic_loader->loadRectangleShape();
  body->setSize({40, 40});
  body->setOrigin({20, 20});
  body->setPosition({player_pos.position.x, player_pos.position.y});
  body->setTexture(item_sprite.getTexture());
  body->setRotation(90.0);

  SpinningItem item_obj = {t_item_type,
                           value,
                           item_sprite,
                           player_pos,
                           AnimationTime{.current_animation_time = 0,
                                         .display_time = 0.06,
                                         .last_timer = 0},
                           body};
  t_em->Assign<SpinningItem>(item, item_obj);
}

void initShoot(std::shared_ptr<Action> t_action,
               std::shared_ptr<EntityManager> t_em,
               rtype::IGraphicLoader *t_graphic_loader,
               UdpServer *t_server_com) {
  Player *player = (*t_em.get()).Get<Player>(t_action->getId());
  EntityID bullet = t_em->createNewEntity();
  SpriteECS sprite =
    SpriteECS("./../Client/sprites/shoot2.png", t_graphic_loader);
  rtype::Vector2f bullet_pos = {player->position.position.x - 20,
                                player->position.position.y +
                                  player->body->getSize().y / 2 - 10};
  rtype::IRectangleShape *bullet_body = t_graphic_loader->loadRectangleShape();

  bullet_body->setSize({20, 20});
  bullet_body->setPosition({bullet_pos.x, bullet_pos.y});
  bullet_body->setTexture(sprite.getTexture());

  std::cout << "init bullet with owner id: "
            << std::to_string(t_action->getId()) << std::endl;
  t_em->Assign<Bullet>(
    bullet, Bullet{bullet_body, 10.0, bullet_pos, t_action->getId()});
  t_server_com->addEvent(std::make_shared<Action>(CreateAction(
    bullet, Action::ObjectType::BULLET, bullet_pos, t_action->getId(),
    player->damage_factor, std::to_string(Action::ShootingType::NORMAL))));
}

// TODO: replace by actual fire shoot
void initFireShoot(std::shared_ptr<Action> t_action,
                   std::shared_ptr<EntityManager> t_em,
                   rtype::IGraphicLoader *t_graphic_loader,
                   UdpServer *t_server_com) {
  Player *player = (*t_em.get()).Get<Player>(t_action->getId());
  EntityID bullet = t_em->createNewEntity();
  SpriteECS sprite =
    SpriteECS("./../Client/sprites/shoot3.png", t_graphic_loader);
  rtype::Vector2f bullet_pos = {player->position.position.x - 20,
                                player->position.position.y +
                                  player->body->getSize().y / 2 - 10};
  rtype::IRectangleShape *bullet_body = t_graphic_loader->loadRectangleShape();

  bullet_body->setSize({20, 20});
  bullet_body->setPosition({bullet_pos.x, bullet_pos.y});
  bullet_body->setTexture(sprite.getTexture());

  t_em->Assign<Bullet>(
    bullet, Bullet{bullet_body, 10.0, bullet_pos, t_action->getId()});
  t_server_com->addEvent(std::make_shared<Action>(CreateAction(
    bullet, Action::ObjectType::BULLET, bullet_pos, t_action->getId(),
    player->damage_factor, std::to_string(Action::ShootingType::FIRE))));
}

// TODO: replace by actual bomb shoot
void initBombShoot(std::shared_ptr<Action> t_action,
                   std::shared_ptr<EntityManager> t_em,
                   rtype::IGraphicLoader *t_graphic_loader,
                   UdpServer *t_server_com) {
  Player *player = (*t_em.get()).Get<Player>(t_action->getId());
  EntityID bullet = t_em->createNewEntity();
  SpriteECS sprite =
    SpriteECS("./../Client/sprites/shoot4.png", t_graphic_loader);
  rtype::Vector2f bullet_pos = {player->position.position.x - 20,
                                player->position.position.y +
                                  player->body->getSize().y / 2 - 10};
  rtype::IRectangleShape *bullet_body = t_graphic_loader->loadRectangleShape();

  bullet_body->setSize({20, 20});
  bullet_body->setPosition({bullet_pos.x, bullet_pos.y});
  bullet_body->setTexture(sprite.getTexture());

  t_em->Assign<Bullet>(
    bullet, Bullet{bullet_body, 10.0, bullet_pos, t_action->getId()});
  t_server_com->addEvent(std::make_shared<Action>(CreateAction(
    bullet, Action::ObjectType::BULLET, bullet_pos, t_action->getId(),
    player->damage_factor, std::to_string(Action::ShootingType::BOMB))));
}

void loadMusic(rtype::IMusic *t_music, bool t_play) {
  if (!t_music->openFromFile(assetLoader.getMusicPath())) {
    std::cout << "Error while loading music" << std::endl;
  }
  t_music->setVolume(50);
  t_music->setLoop(true);
  if (t_play) t_music->play(level - 1);
}

void initBackground(std::shared_ptr<EntityManager> t_entity_manager,
                    rtype::IGraphicLoader *t_graphic_loader) {
  int index = 0;
  for (Json::Value background : assetLoader.getBackgroundData()) {
    EntityID background_entity;
    if (index < background_entities.size()) {
      background_entity = background_entities[index];
    } else {
      background_entity = t_entity_manager->createNewEntity();
      background_entities.push_back(background_entity);
    }
    BackgroundLayer background_layer = BackgroundLayer{
      SpriteECS(
        background["path"].asString(), t_graphic_loader,
        {background["scale"]["x"].asFloat(),
         background["scale"]["y"].asFloat()},
        rtype::Color{
          static_cast<unsigned char>(background["color"]["r"].asInt()),
          static_cast<unsigned char>(background["color"]["g"].asInt()),
          static_cast<unsigned char>(background["color"]["b"].asInt()),
          static_cast<unsigned char>(background["color"]["a"].asInt())}),
      {background["position"]["x"].asFloat(),
       background["position"]["y"].asFloat()},
      background["speed"].asFloat() * assetLoader.getBackgroundSpeed(),
      background["limit"].asInt()};
    t_entity_manager->Assign<BackgroundLayer>(background_entity,
                                              background_layer);
    index++;
  }
}
