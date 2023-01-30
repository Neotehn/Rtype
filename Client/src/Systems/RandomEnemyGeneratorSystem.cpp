#include "RandomEnemyGeneratorSystem.hpp"

RandomEnemyGeneratorSystem::RandomEnemyGeneratorSystem(
    std::shared_ptr<EntityManager> t_em) {
  m_em = t_em;
}

RandomEnemyGeneratorSystem::~RandomEnemyGeneratorSystem() {}

void RandomEnemyGeneratorSystem::updateData(SystemData &t_data) {}

void RandomEnemyGeneratorSystem::update() {
  int random = rand() % 100;
  if (random < 1) {
    EntityID enemy = m_em->createNewEntity();
    SpriteECS sprite = SpriteECS("./sprites/r-typesheet30a.gif");
    sf::Vector2f enemy_pos = {800, rand() % 600 + 100};
    m_em->Assign<std::string>(enemy, "enemy");
    m_em->Assign<Pos>(enemy, {{-7, rand() % 3 - 1}, enemy_pos});

    sf::RectangleShape body;
    body.setSize({30, 30});
    body.setPosition(enemy_pos);
    body.setTexture(sprite.getTexture());
    m_em->Assign<sf::RectangleShape>(enemy, body);
  }
}
