#ifndef CLIENT_SRC_SYSTEMS_SHOOTINGSYSTEM_HPP_
#define CLIENT_SRC_SYSTEMS_SHOOTINGSYSTEM_HPP_

#include <memory>

#include "../ECS/ISystem.hpp"
#include "../../Client/src/Action/Action.hpp"
#include "../../Server/Protocol/UdpServer.hpp"

class ShootingSystem : public ISystem {
 public:
  ShootingSystem(std::shared_ptr<EntityManager> t_em, UdpServer *t_serverCom);
  ~ShootingSystem();

  void update();
  void updateData(SystemData &t_data);

 private:
  EventQueue m_event_queue;
  UdpServer *m_serverCom;

  void shoot(std::shared_ptr<Action> action);
  void shootFire(std::shared_ptr<Action> action);
  void shootBomb(std::shared_ptr<Action> action);
};

#endif  // CLIENT_SRC_SYSTEMS_SHOOTINGSYSTEM_HPP_
