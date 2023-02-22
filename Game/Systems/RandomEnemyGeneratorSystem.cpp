#include "RandomEnemyGeneratorSystem.hpp"

RandomEnemyGeneratorSystem::RandomEnemyGeneratorSystem(
  std::shared_ptr<EntityManager> t_em, UdpServer *t_serverCom,
  rtype::IGraphicLoader *t_graphic_loader) {
  m_em = t_em;
  m_serverCom = t_serverCom;
  m_graphic_loader = t_graphic_loader;
}

RandomEnemyGeneratorSystem::~RandomEnemyGeneratorSystem() {}

void RandomEnemyGeneratorSystem::updateData(SystemData &t_data) {}

void RandomEnemyGeneratorSystem::update() {
  int random = rand() % 1000;
  generateEnemy(random);
  generatePowerUp(random);
}

void RandomEnemyGeneratorSystem::generateEnemy(int random) {
  if (random < 10) {
    EntityID enemy = m_em->createNewEntity();
    SpriteECS sprite =
      SpriteECS("./../Client/sprites/r-typesheet30a.gif", m_graphic_loader);
    rtype::Vector2f enemy_pos = {800, float(rand() % 600 + 100)};
    float velocity_direction = float(rand() % 3 - 1);

    rtype::IRectangleShape *body = m_graphic_loader->loadRectangleShape();
    body->setSize({30, 30});
    body->setPosition({enemy_pos.x, enemy_pos.y});
    body->setTexture(sprite.getTexture());
    body->setTextureRect(rtype::IntRect{0, 0, 34, 34});

    AnimationObj enemy_obj =
      AnimationObj{"enemy", Pos{{-7, velocity_direction}, enemy_pos},
                   AnimationTime{.current_animation_time = 0,
                                 .display_time = 1,
                                 .last_timer = 0},
                   AnimationRect{.size = 34, .limit = 68}, body};
    m_em->Assign<AnimationObj>(enemy, enemy_obj);
    m_serverCom->addEvent(std::make_shared<Action>(CreateAction(
      enemy, Action::ObjectType::ENEMY, enemy_pos, "", velocity_direction)));
  }
}

void RandomEnemyGeneratorSystem::generatePowerUp(int random) {
  if (random > 998) {
    int random_powerup = rand() % 5;
    if (random_powerup == 0) {
      createCoin();
    } else if (random_powerup == 1) {
      createItem("../Client/sprites/powerup/life_item.png",
                 rtype::ItemType::LIFE_ITEM, 1);
    } else if (random_powerup == 2) {
      createItem("../Client/sprites/powerup/speed_item.png",
                 rtype::ItemType::SPEED_ITEM, 3);
    } else if (random_powerup == 3) {
      createItem("../Client/sprites/powerup/bomb_item.png",
                 rtype::ItemType::BOMB_ITEM, 5);
    } else {
      createItem("../Client/sprites/powerup/fire_item.png",
                 rtype::ItemType::FIRE_ITEM, 5);
    }
  }
}

void RandomEnemyGeneratorSystem::createCoin() {
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

void RandomEnemyGeneratorSystem::createItem(std::string t_path,
                                            rtype::ItemType t_type,
                                            int t_value) {
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
