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
  if (random < 10) {
    initEnemy(m_em, m_graphic_loader, m_serverCom);
  } else if (random < 15) {
    createCoin(m_em, m_graphic_loader, m_serverCom);
  } else if (random > 997) {
    initPowerUp(m_em, m_graphic_loader, m_serverCom);
  }
}
