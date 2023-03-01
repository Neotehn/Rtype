#ifndef CLIENT_SRC_SYSTEMS_SHOOTINGSYSTEM_HPP_
#define CLIENT_SRC_SYSTEMS_SHOOTINGSYSTEM_HPP_

#include <memory>

#include "../CreateEntities/Init.hpp"
#include "../ECS/ISystem.hpp"
#include "../../Client/src/Action/Action.hpp"
#include "../../Server/Protocol/UdpServer.hpp"

class ShootingSystem : public ISystem {
 public:
  ShootingSystem(std::shared_ptr<EntityManager> t_em, UdpServer *t_serverCom,
                 rtype::IGraphicLoader *t_graphic_loader);
  ~ShootingSystem() = default;

  void update() override;
  void updateData(SystemData &t_data) override;

 private:
  EventQueue m_event_queue;
  UdpServer *m_serverCom;
  rtype::IGraphicLoader *m_graphic_loader;

  void shootMoney(std::shared_ptr<Action> t_action);
  void shootFire(std::shared_ptr<Action> t_action);
  void shootBomb(std::shared_ptr<Action> t_action);
};

#endif  // CLIENT_SRC_SYSTEMS_SHOOTINGSYSTEM_HPP_
