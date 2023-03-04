# RandomEnemyGeneratorSystem

This system will generate enemies and power ups at random locations.

RandomEnemyGeneratorSystem.hpp

```
#ifndef CLIENT_SRC_SYSTEMS_RANDOMENEMYGENERATORSYSTEM_HPP_
#define CLIENT_SRC_SYSTEMS_RANDOMENEMYGENERATORSYSTEM_HPP_

#include <memory>
#include <string>

#include "../CreateEntities/Init.hpp"
#include "../ECS/ISystem.hpp"
#include "../ECS/DataTypesECS.hpp"
#include "../../Server/Protocol/UdpServer.hpp"

class RandomEnemyGeneratorSystem : public ISystem {
 public:
  RandomEnemyGeneratorSystem(std::shared_ptr<EntityManager> t_em,
                             UdpServer *t_serverCom,
                             rtype::IGraphicLoader *t_graphic_loader);
  ~RandomEnemyGeneratorSystem();

  void update();
  void updateData(SystemData &t_data);

 private:
  std::shared_ptr<EntityManager> m_em;
  UdpServer *m_serverCom;
  rtype::IGraphicLoader *m_graphic_loader;
};

#endif  // CLIENT_SRC_SYSTEMS_RANDOMENEMYGENERATORSYSTEM_HPP_
```

RandomEnemyGeneratorSystem.cpp

```
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
```

[Back](../game-engine/systems.md)
