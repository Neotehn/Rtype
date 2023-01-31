#ifndef CLIENT_SRC_SYSTEMS_RANDOMENEMYGENERATORSYSTEM_HPP_
#define CLIENT_SRC_SYSTEMS_RANDOMENEMYGENERATORSYSTEM_HPP_

#include "../../../ECS/ISystem.hpp"

class RandomEnemyGeneratorSystem : public ISystem {
 public:
  RandomEnemyGeneratorSystem(std::shared_ptr<EntityManager> t_em);
  ~RandomEnemyGeneratorSystem();

  void update();
  void updateData(SystemData &t_data);

 private:
  std::shared_ptr<EntityManager> m_em;
};

#endif  // CLIENT_SRC_SYSTEMS_RANDOMENEMYGENERATORSYSTEM_HPP_
