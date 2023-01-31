#ifndef CLIENT_SRC_SYSTEMS_SHOOTINGSYSTEM_HPP_
#define CLIENT_SRC_SYSTEMS_SHOOTINGSYSTEM_HPP_

#include "../../../ECS/ISystem.hpp"

class ShootingSystem : public ISystem {
 public:
  ShootingSystem(std::shared_ptr<EntityManager> t_em);
  ~ShootingSystem();

  void update();
  void updateData(SystemData &t_data);

 private:
  EventQueue m_event_queue;
};

#endif  // CLIENT_SRC_SYSTEMS_SHOOTINGSYSTEM_HPP_
