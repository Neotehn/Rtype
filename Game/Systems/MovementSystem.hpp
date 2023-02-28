#ifndef CLIENT_SRC_SYSTEMS_MOVEMENTSYSTEM_HPP_
#define CLIENT_SRC_SYSTEMS_MOVEMENTSYSTEM_HPP_

#include <string>

#include "../ECS/DataTypesECS.hpp"
#include "../ECS/ISystem.hpp"
#include "../../Client/src/Action/Action.hpp"
#include "../../Server/Protocol/UdpServer.hpp"
#include "../../Client/Protocol/UdpClient.hpp"

class MovementSystem : public ISystem {
 public:
  MovementSystem(std::shared_ptr<EntityManager> t_em, UdpServer *t_serverCom);
  MovementSystem(std::shared_ptr<EntityManager> t_em, UdpServer *t_serverCom,
                 UdpClient *t_clientCom);
  ~MovementSystem();

  void update();
  void updateData(SystemData &t_data);

 private:
  EventQueue m_event_queue;
  UdpServer *m_serverCom;
  UdpClient *m_clientCom;

  void updatePlayer(EntityID t_ent);
  void updatePlayerClient(EntityID t_ent);
  void updateBackground(EntityID t_ent);
  void updateBullets(EntityID t_ent);
  void updateBulletsServer(EntityID t_ent);
};

#endif  // CLIENT_SRC_SYSTEMS_MOVEMENTSYSTEM_HPP_
