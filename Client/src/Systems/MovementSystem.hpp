#ifndef CLIENT_SRC_SYSTEMS_MOVEMENTSYSTEM_HPP_
#define CLIENT_SRC_SYSTEMS_MOVEMENTSYSTEM_HPP_

#include <string>

#include "../../../ECS/DataTypesECS.hpp"
#include "../../../ECS/ISystem.hpp"

class MovementSystem : public ISystem {
 public:
  MovementSystem(std::shared_ptr<EntityManager> t_em);
  ~MovementSystem();

  void update();
  void updateData(SystemData &t_data);

  void updatePlayer(EntityID t_ent);
  void updateBackground(EntityID t_ent);
  void updateBullets(EntityID t_ent);

 private:
  EventQueue m_event_queue;
};

#endif  // CLIENT_SRC_SYSTEMS_MOVEMENTSYSTEM_HPP_
