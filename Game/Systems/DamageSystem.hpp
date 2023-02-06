#ifndef CLIENT_SRC_SYSTEMS_DAMAGESYSTEM_HPP_
#define CLIENT_SRC_SYSTEMS_DAMAGESYSTEM_HPP_

#include <string>
#include <memory>

#include "../ECS/DataTypesECS.hpp"
#include "../ECS/ISystem.hpp"
#include "../../Client/src/Action/Action.hpp"

class DamageSystem : public ISystem {
 public:
  DamageSystem(std::shared_ptr<EntityManager> t_em);
  ~DamageSystem();

  virtual void update();
  virtual void updateData(SystemData &t_data);

 private:
  EventQueue m_event_queue;
};

#endif  // CLIENT_SRC_SYSTEMS_DAMAGESYSTEM_HPP_
