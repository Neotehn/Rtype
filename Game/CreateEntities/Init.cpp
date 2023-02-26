#include "Init.hpp"
#include <string>
#include <vector>

AssetLoader assetLoader;
int level = 0;

void loadLevel(int t_level) {
  level = t_level;
  assetLoader.loadLevel(t_level);
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
  Player player_obj = Player{player_sprite, player_pos, body, health, 10};
  t_entity_manager->Assign<Player>(player, player_obj);
  t_serverCom->addEvent(std::make_shared<Action>(
    CreateAction(player, Action::ObjectType::PLAYER, player_pos.position,
                 "../Client/sprites/starship.png")));
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
                      std::shared_ptr<EntityManager> m_em,
                      rtype::IGraphicLoader *m_graphic_loader) {
  EntityID bullet = m_em->createNewEntity(t_id);

  rtype::IRectangleShape *bullet_body = m_graphic_loader->loadRectangleShape();
  bullet_body->setSize({20, 20});
  bullet_body->setPosition({t_pos.x, t_pos.y});

  switch (t_shooting_type) {
    case Action::ShootingType::NORMAL:
      bullet_body->setTexture(
        SpriteECS("./../Client/sprites/shoot2.png", m_graphic_loader)
          .getTexture());
      break;
    case Action::ShootingType::FIRE:
      bullet_body->setTexture(
        SpriteECS("./../Client/sprites/shoot3.png", m_graphic_loader)
          .getTexture());
      break;
    case Action::ShootingType::BOMB:
      bullet_body->setTexture(
        SpriteECS("./../Client/sprites/shoot4.png", m_graphic_loader)
          .getTexture());
      break;
  }
  Bullet displayable_bullet = Bullet{bullet_body, 10.0, t_pos};
  m_em->Assign<Bullet>(bullet, displayable_bullet);
}

void initEnemy(std::shared_ptr<EntityManager> m_em,
               rtype::IGraphicLoader *m_graphic_loader,
               UdpServer *m_serverCom) {
  Json::Value enemy_data = assetLoader.getEnemyData()[0];
  int size = enemy_data["size"].asInt();
  EntityID enemy = m_em->createNewEntity();
  SpriteECS sprite = SpriteECS(enemy_data["path"].asString(), m_graphic_loader);
  rtype::Vector2f enemy_pos = {800, float(rand() % 600 + 100)};
  float velocity_direction = float(rand() % 3 - 1);

  rtype::IRectangleShape *body = m_graphic_loader->loadRectangleShape();
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
  m_em->Assign<AnimationObj>(enemy, enemy_obj);
  m_serverCom->addEvent(std::make_shared<Action>(CreateAction(
    enemy, Action::ObjectType::ENEMY, enemy_pos, "", velocity_direction)));
}

void initEnemyClient(EntityID t_id, rtype::Vector2f t_pos, float t_velocity,
                     std::shared_ptr<EntityManager> m_em,
                     rtype::IGraphicLoader *m_graphic_loader) {
  Json::Value enemy_data = assetLoader.getEnemyData()[0];
  int size = enemy_data["size"].asInt();
  EntityID enemy = m_em->createNewEntity(t_id);
  SpriteECS sprite = SpriteECS(enemy_data["path"].asString(), m_graphic_loader);
  rtype::IRectangleShape *body = m_graphic_loader->loadRectangleShape();
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
  m_em->Assign<AnimationObj>(enemy, enemy_obj);
}

void initExplosionClient(EntityID t_id, rtype::Vector2f t_pos,
                         std::shared_ptr<EntityManager> m_em,
                         rtype::IGraphicLoader *m_graphic_loader) {
  EntityID explosion = m_em->createNewEntity(t_id);
  SpriteECS sprite =
    SpriteECS("./../Client/sprites/explosion/Explosion.png", m_graphic_loader);
  rtype::IRectangleShape *body = m_graphic_loader->loadRectangleShape();
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
  m_em->Assign<AnimationObj>(explosion, explosion_obj);
}

void createCoin(std::shared_ptr<EntityManager> m_em,
                rtype::IGraphicLoader *m_graphic_loader,
                UdpServer *m_serverCom) {
  EntityID powerup = m_em->createNewEntity();
  SpriteECS sprite =
    SpriteECS("./../Client/sprites/powerup/coin.png", m_graphic_loader);
  rtype::Vector2f powerup_pos = {800, float(rand() % 600 + 100)};

  rtype::IRectangleShape *body = m_graphic_loader->loadRectangleShape();
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
  m_em->Assign<AnimationObj>(powerup, powerup_obj);

  m_serverCom->addEvent(std::make_shared<Action>(
    CreateAction(powerup, Action::ObjectType::POWER_UP, powerup_pos, "", 0)));
}

void createItem(std::string t_path, rtype::ItemType t_type, int t_value,
                std::shared_ptr<EntityManager> m_em,
                rtype::IGraphicLoader *m_graphic_loader,
                UdpServer *m_serverCom) {
  EntityID powerup = m_em->createNewEntity();
  SpriteECS sprite = SpriteECS(t_path, m_graphic_loader);
  rtype::Vector2f powerup_pos = {800, float(rand() % 600 + 100)};

  rtype::IRectangleShape *body = m_graphic_loader->loadRectangleShape();
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
  m_em->Assign<SpinningItem>(powerup, item_obj);

  m_serverCom->addEvent(std::make_shared<Action>(
    CreateAction(powerup, Action::ObjectType::ITEM, powerup_pos, "", t_type)));
}

void initPowerUp(std::shared_ptr<EntityManager> m_em,
                 rtype::IGraphicLoader *m_graphic_loader,
                 UdpServer *m_serverCom) {
  int random_powerup = rand() % 5;
  if (random_powerup == 0) {
    createCoin(m_em, m_graphic_loader, m_serverCom);
  } else if (random_powerup == 1) {
    createItem("../Client/sprites/powerup/life_item.png",
               rtype::ItemType::LIFE_ITEM, 1, m_em, m_graphic_loader,
               m_serverCom);
  } else if (random_powerup == 2) {
    createItem("../Client/sprites/powerup/speed_item.png",
               rtype::ItemType::SPEED_ITEM, 3, m_em, m_graphic_loader,
               m_serverCom);
  } else if (random_powerup == 3) {
    createItem("../Client/sprites/powerup/bomb_item.png",
               rtype::ItemType::BOMB_ITEM, 5, m_em, m_graphic_loader,
               m_serverCom);
  } else {
    createItem("../Client/sprites/powerup/fire_item.png",
               rtype::ItemType::FIRE_ITEM, 5, m_em, m_graphic_loader,
               m_serverCom);
  }
}

void initPowerUpClient(EntityID t_id, rtype::Vector2f t_pos,
                       std::shared_ptr<EntityManager> m_em,
                       rtype::IGraphicLoader *m_graphic_loader) {
  EntityID powerup = m_em->createNewEntity(t_id);
  SpriteECS sprite =
    SpriteECS("./../Client/sprites/powerup/coin.png", m_graphic_loader);
  rtype::IRectangleShape *body = m_graphic_loader->loadRectangleShape();
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
  m_em->Assign<AnimationObj>(powerup, power_up);
}

void initItemClient(EntityID t_id, rtype::ItemType t_item_type,
                    rtype::Vector2f t_pos, std::shared_ptr<EntityManager> m_em,
                    rtype::IGraphicLoader *m_graphic_loader) {
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
  EntityID item = m_em->createNewEntity(t_id);
  SpriteECS item_sprite = SpriteECS(path, m_graphic_loader);

  Pos player_pos = Pos{rtype::Vector2f{-7, 0}, t_pos};

  rtype::IRectangleShape *body = m_graphic_loader->loadRectangleShape();
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
  m_em->Assign<SpinningItem>(item, item_obj);
}

void initShoot(std::shared_ptr<Action> action,
               std::shared_ptr<EntityManager> m_em,
               rtype::IGraphicLoader *m_graphic_loader,
               UdpServer *m_serverCom) {
  Player *player = (*m_em.get()).Get<Player>(action->getId());
  EntityID bullet = m_em->createNewEntity();
  SpriteECS sprite =
    SpriteECS("./../Client/sprites/shoot2.png", m_graphic_loader);
  rtype::Vector2f bullet_pos = {player->position.position.x - 20,
                                player->position.position.y +
                                  player->body->getSize().y / 2 - 10};
  rtype::IRectangleShape *bullet_body = m_graphic_loader->loadRectangleShape();

  bullet_body->setSize({20, 20});
  bullet_body->setPosition({bullet_pos.x, bullet_pos.y});
  bullet_body->setTexture(sprite.getTexture());

  m_em->Assign<Bullet>(bullet, Bullet{bullet_body, 10.0, bullet_pos});
  m_serverCom->addEvent(std::make_shared<Action>(
    CreateAction(bullet, Action::ObjectType::BULLET, bullet_pos,
                 std::to_string(Action::ShootingType::NORMAL))));
}

// TODO: replace by actual fire shoot
void initFireShoot(std::shared_ptr<Action> action,
                   std::shared_ptr<EntityManager> m_em,
                   rtype::IGraphicLoader *m_graphic_loader,
                   UdpServer *m_serverCom) {
  Player *player = (*m_em.get()).Get<Player>(action->getId());
  EntityID bullet = m_em->createNewEntity();
  SpriteECS sprite =
    SpriteECS("./../Client/sprites/shoot3.png", m_graphic_loader);
  rtype::Vector2f bullet_pos = {player->position.position.x - 20,
                                player->position.position.y +
                                  player->body->getSize().y / 2 - 10};
  rtype::IRectangleShape *bullet_body = m_graphic_loader->loadRectangleShape();

  bullet_body->setSize({20, 20});
  bullet_body->setPosition({bullet_pos.x, bullet_pos.y});
  bullet_body->setTexture(sprite.getTexture());

  m_em->Assign<Bullet>(bullet, Bullet{bullet_body, 10.0, bullet_pos});
  m_serverCom->addEvent(std::make_shared<Action>(
    CreateAction(bullet, Action::ObjectType::BULLET, bullet_pos,
                 std::to_string(Action::ShootingType::FIRE))));
}

// TODO: replace by actual bomb shoot
void initBombShoot(std::shared_ptr<Action> action,
                   std::shared_ptr<EntityManager> m_em,
                   rtype::IGraphicLoader *m_graphic_loader,
                   UdpServer *m_serverCom) {
  Player *player = (*m_em.get()).Get<Player>(action->getId());
  EntityID bullet = m_em->createNewEntity();
  SpriteECS sprite =
    SpriteECS("./../Client/sprites/shoot4.png", m_graphic_loader);
  rtype::Vector2f bullet_pos = {player->position.position.x - 20,
                                player->position.position.y +
                                  player->body->getSize().y / 2 - 10};
  rtype::IRectangleShape *bullet_body = m_graphic_loader->loadRectangleShape();

  bullet_body->setSize({20, 20});
  bullet_body->setPosition({bullet_pos.x, bullet_pos.y});
  bullet_body->setTexture(sprite.getTexture());

  m_em->Assign<Bullet>(bullet, Bullet{bullet_body, 10.0, bullet_pos});
  m_serverCom->addEvent(std::make_shared<Action>(
    CreateAction(bullet, Action::ObjectType::BULLET, bullet_pos,
                 std::to_string(Action::ShootingType::BOMB))));
}

void loadMusic(rtype::IMusic *m_music) {
  if (!m_music->openFromFile(assetLoader.getMusicPath())) {
    std::cout << "Error while loading music" << std::endl;
  }
  m_music->setVolume(50);
  m_music->setLoop(true);
}

void initBackground(EntityManager &t_entity_manager,
                    rtype::IGraphicLoader *t_graphic_loader) {
  for (Json::Value background : assetLoader.getBackgroundData()) {
    EntityID background_entity = t_entity_manager.createNewEntity();
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
      background["speed"].asFloat(),
      background["limit"].asInt()};
    t_entity_manager.Assign<BackgroundLayer>(background_entity,
                                             background_layer);
  }
}
