#ifndef CLIENT_SRC_SYSTEMS_SHOOTINGSYSTEM_HPP_
#define CLIENT_SRC_SYSTEMS_SHOOTINGSYSTEM_HPP_

#include <memory>

#include "../ECS/ISystem.hpp"
#include "../../Client/src/Action/Action.hpp"
#include "../../Server/Protocol/UdpServer.hpp"

class ShootingSystem : public ISystem {
 public:
  ShootingSystem(std::shared_ptr<EntityManager> t_em, UdpServer *t_serverCom,
                 rtype::IGraphicLoader *t_graphic_loader);
  ~ShootingSystem();

  void update();
  void updateData(SystemData &t_data);

 private:
  EventQueue m_event_queue;
  UdpServer *m_serverCom;
  rtype::IGraphicLoader *m_graphic_loader;

  void shoot(std::shared_ptr<Action> action);
  void shootFire(std::shared_ptr<Action> action);
  void shootBomb(std::shared_ptr<Action> action);
};

#endif  // CLIENT_SRC_SYSTEMS_SHOOTINGSYSTEM_HPP_
