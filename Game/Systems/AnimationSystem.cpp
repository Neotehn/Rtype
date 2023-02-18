#include "AnimationSystem.hpp"

AnimationSystem::AnimationSystem(std::shared_ptr<EntityManager> t_em,
                                 InputManager &t_input_manager)
    : m_input_manager(t_input_manager) {
  m_em = t_em;
  m_timer = Timer();
  m_timer.startTimer();
}

AnimationSystem::~AnimationSystem() {}

void AnimationSystem::updateData(SystemData &t_data) {}

void AnimationSystem::update() {
  for (EntityID ent : EntityViewer<AnimationObj>(*m_em.get())) {
    AnimationObj *anim = (*m_em.get()).Get<AnimationObj>(ent);

    if (anim->time.last_timer == 0) {
      anim->time.last_timer = m_timer.returnTime();
    }
    if (anim->time.current_animation_time >= anim->time.display_time) {
      anim->time.current_animation_time = 0;
      rtype::IntRect rect = anim->body->getTextureRect();
      if (rect.left >= anim->rect.limit) {
        if (anim->type == "explosion") {
          m_input_manager.addActionsToQueue(
            std::make_shared<Action>(DestroyAction(ent)));
        } else {
          rect.left = 0;
        }
      } else {
        rect.left += anim->rect.size;
      }
      anim->body->setTextureRect(rect);
    }
    anim->time.current_animation_time +=
      m_timer.returnTime() - anim->time.last_timer;
    anim->time.last_timer = m_timer.returnTime();
  }
}
