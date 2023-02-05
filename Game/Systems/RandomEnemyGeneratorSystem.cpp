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
  if (random < 1) {
    EntityID enemy = m_em->createNewEntity();
    SpriteECS sprite = SpriteECS("./../Client/sprites/r-typesheet30a.gif");
    sf::Vector2f enemy_pos = {800, float(rand() % 600 + 100)};
    float velocity_direction = float(rand() % 3 - 1);
    m_em->Assign<std::string>(enemy, "enemy");
    m_em->Assign<Pos>(enemy, {{-7, velocity_direction}, enemy_pos});
    m_em->Assign<AnimationTime>(
      enemy, {.current_animation_time = 0, .display_time = 1, .last_timer = 0});
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
