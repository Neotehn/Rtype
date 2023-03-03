#ifndef R_TYPE_CLIENT_CREATEPLAYERSYSTEM_HPP
#define R_TYPE_CLIENT_CREATEPLAYERSYSTEM_HPP

#include "../ECS/ISystem.hpp"
#include "../../Server/Protocol/UdpServer.hpp"
#include "../CreateEntities/Init.hpp"

class CreatePlayerSystem : public ISystem {
 public:
  CreatePlayerSystem(std::shared_ptr<EntityManager> t_em,
                     UdpServer *t_server_com,
                     rtype::IGraphicLoader *t_graphic_loader);
  ~CreatePlayerSystem() = default;

  void update() override;
  void updateData(SystemData &t_data) override;

 private:
  std::shared_ptr<EntityManager> m_em;
  EventQueue m_event_queue;
  UdpServer *m_server_com;
  std::vector<int> m_registered_players;
  rtype::IGraphicLoader *m_graphic_loader;

  bool isRegistered(int t_id);
};

#endif  //R_TYPE_CLIENT_CREATEPLAYERSYSTEM_HPP
