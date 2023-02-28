#ifndef CLIENT_SRC_SYSTEMS_ANIMATIONSYSTEM_HPP_
#define CLIENT_SRC_SYSTEMS_ANIMATIONSYSTEM_HPP_

#include <memory>
#include <string>

#include "../ECS/ISystem.hpp"
#include "../Timer.hpp"
#include "../ECS/DataTypesECS.hpp"
#include "../../Client/src/InputManager/InputManager.hpp"
#include "../../Client/src/Action/DestroyAction.hpp"

class AnimationSystem : public ISystem {
 public:
  AnimationSystem(std::shared_ptr<EntityManager> t_em,
                  InputManager &t_input_manager);
  ~AnimationSystem();

  void update();
  void updateData(SystemData &t_data);

 private:
  Timer m_timer;
  InputManager &m_input_manager;

  void generalAnimation(EntityID t_ent, AnimationObj *anim);
  void animateAnimationObj();
  void animateSpinningItem();
};

#endif  // CLIENT_SRC_SYSTEMS_ANIMATIONSYSTEM_HPP_
