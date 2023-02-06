#ifndef CLIENT_SRC_SYSTEMS_ANIMATIONSYSTEM_HPP_
#define CLIENT_SRC_SYSTEMS_ANIMATIONSYSTEM_HPP_

#include "../ECS/ISystem.hpp"
#include "../Timer.hpp"
#include "../ECS/DataTypesECS.hpp"

class AnimationSystem : public ISystem {
 public:
  AnimationSystem(std::shared_ptr<EntityManager> t_em);
  ~AnimationSystem();

  void update();
  void updateData(SystemData &t_data);

 private:
  Timer m_timer;
};

#endif  // CLIENT_SRC_SYSTEMS_ANIMATIONSYSTEM_HPP_
