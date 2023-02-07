#include "RandomEnemyGeneratorSystem.hpp"

RandomEnemyGeneratorSystem::RandomEnemyGeneratorSystem(
  std::shared_ptr<EntityManager> t_em, UdpServer *t_serverCom) {
  m_em = t_em;
  m_serverCom = t_serverCom;
}

RandomEnemyGeneratorSystem::~RandomEnemyGeneratorSystem() {}

void RandomEnemyGeneratorSystem::updateData(SystemData &t_data) {}

void RandomEnemyGeneratorSystem::update() {
  int random = rand() % 100;
  generateEnemy(random);
  generatePowerUp(random);
}

void RandomEnemyGeneratorSystem::generateEnemy(int random) {
  if (random < 1) {
    EntityID enemy = m_em->createNewEntity();
    SpriteECS sprite = SpriteECS("./../Client/sprites/r-typesheet30a.gif");
    sf::Vector2f enemy_pos = {800, float(rand() % 600 + 100)};
    float velocity_direction = float(rand() % 3 - 1);
    m_em->Assign<std::string>(enemy, "enemy");
    m_em->Assign<Pos>(enemy, {{-7, velocity_direction}, enemy_pos});
    m_em->Assign<AnimationTime>(
      enemy, {.current_animation_time = 0, .display_time = 1, .last_timer = 0});
    m_em->Assign<AnimationRect>(enemy, {.size = 34, .limit = 68});
    sf::RectangleShape body;
    body.setSize({30, 30});
    body.setPosition(enemy_pos);
    body.setTexture(sprite.getTexture());
    body.setTextureRect(sf::IntRect(0, 0, 34, 34));
    m_em->Assign<sf::RectangleShape>(enemy, body);
    m_serverCom->addEvent(std::make_shared<Action>(CreateAction(
      enemy, Action::ObjectType::ENEMY, enemy_pos, "", velocity_direction)));
  }
}

void RandomEnemyGeneratorSystem::generatePowerUp(int random) {
  if (random > 98) {
    if ((rand() % 10) < 1) {
      EntityID powerup = m_em->createNewEntity();
      SpriteECS sprite = SpriteECS("./../Client/sprites/powerup/coin.png");
      m_em->Assign<std::string>(powerup, "powerup");
      sf::Vector2f powerup_pos = {800, float(rand() % 600 + 100)};
      m_em->Assign<Pos>(powerup, {{-7, 0}, powerup_pos});
      m_em->Assign<AnimationTime>(
        powerup,
        {.current_animation_time = 0, .display_time = 0.1, .last_timer = 0});
      m_em->Assign<AnimationRect>(powerup, {.size = 84, .limit = 420});
      sf::RectangleShape body;
      body.setSize({30, 30});
      body.setPosition(powerup_pos);
      body.setTexture(sprite.getTexture());
      body.setTextureRect(sf::IntRect(0, 0, 84, 84));
      m_em->Assign<sf::RectangleShape>(powerup, body);

      m_serverCom->addEvent(std::make_shared<Action>(CreateAction(
        powerup, Action::ObjectType::POWER_UP, powerup_pos, "", 0)));
    }
  }
}
