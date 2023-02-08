#ifndef CLIENT_SRC_SYSTEMS_DESTROYSYSTEM_HPP_
#define CLIENT_SRC_SYSTEMS_DESTROYSYSTEM_HPP_

#include <string>
#include <memory>

#include "../ECS/DataTypesECS.hpp"
#include "../ECS/ISystem.hpp"
#include "../../Client/src/Action/Action.hpp"

class DestroySystem : public ISystem {
 public:
  DestroySystem(std::shared_ptr<EntityManager> t_em);
  ~DestroySystem();

  virtual void update();
  virtual void updateData(SystemData &t_data);

 private:
  EventQueue m_event_queue;
};

#endif  // CLIENT_SRC_SYSTEMS_DESTROYSYSTEM_HPP_
