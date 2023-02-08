#ifndef CLIENT_SRC_SYSTEMS_COLLISIONSYSTEM_HPP_
#define CLIENT_SRC_SYSTEMS_COLLISIONSYSTEM_HPP_

#include <string>

#include "../ECS/ISystem.hpp"
#include "../ECS/DataTypesECS.hpp"
#include "../../Server/Protocol/UdpServer.hpp"

class CollisionSystem : public ISystem {
 public:
  CollisionSystem(std::shared_ptr<EntityManager> t_em, UdpServer *t_serverCom);
  ~CollisionSystem();

  void update();
  void updateData(SystemData &t_data);
  void bulletEnemyCollision();

 private:
  std::shared_ptr<EntityManager> m_em;
  UdpServer *m_serverCom;

  EntityID createExplosion();
};

#endif  // CLIENT_SRC_SYSTEMS_COLLISIONSYSTEM_HPP_
