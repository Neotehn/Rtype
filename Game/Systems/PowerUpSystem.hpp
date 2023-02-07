#ifndef R_TYPE_CLIENT_POWERUPSYSTEM_HPP
#define R_TYPE_CLIENT_POWERUPSYSTEM_HPP

#include <memory>

#include "../ECS/ISystem.hpp"

class PowerUpSystem : public ISystem {
 public:
  PowerUpSystem(std::shared_ptr<EntityManager> t_em);
  ~PowerUpSystem();

  void update();
  void updateData(SystemData &t_data);

 private:
  EventQueue m_event_queue;
};

#endif  //R_TYPE_CLIENT_POWERUPSYSTEM_HPP
