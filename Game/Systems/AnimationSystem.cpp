#include "AnimationSystem.hpp"

AnimationSystem::AnimationSystem(std::shared_ptr<EntityManager> t_em,
                                 InputManager &t_input_manager)
    : m_input_manager(t_input_manager) {
  m_em = t_em;
  m_timer = Timer();
  m_timer.startTimer();
}

void AnimationSystem::updateData(SystemData &t_data) {}

void AnimationSystem::update() {
  animateAnimationObj();
  animateSpinningItem();
}

void AnimationSystem::generalAnimation(EntityID t_ent, AnimationObj *anim) {
  if (anim->time.last_timer == 0) {
    anim->time.last_timer = m_timer.returnTime();
  }
  if (anim->time.current_animation_time >= anim->time.display_time) {
    anim->time.current_animation_time = 0;
    rtype::IntRect rect = anim->body->getTextureRect();
    if (rect.left >= anim->rect.limit) {
      if (anim->type == "explosion") {
        m_input_manager.addActionsToQueue(
          std::make_shared<Action>(DestroyAction(t_ent)));
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

void AnimationSystem::animateAnimationObj() {
  for (EntityID ent : EntityViewer<AnimationObj>(*m_em.get())) {
    AnimationObj *anim = (*m_em.get()).Get<AnimationObj>(ent);
    generalAnimation(ent, anim);
  }
  for (EntityID ent : EntityViewer<Enemy>(*m_em.get())) {
    Enemy *enem = (*m_em.get()).Get<Enemy>(ent);
    if (enem->obj->rect.limit != 0) generalAnimation(ent, enem->obj);
  }
}

void AnimationSystem::animateSpinningItem() {
  for (EntityID ent : EntityViewer<SpinningItem>(*m_em)) {
    SpinningItem *item = (*m_em).Get<SpinningItem>(ent);

    if (item->time.last_timer == 0) {
      item->time.last_timer = m_timer.returnTime();
    }
    if (item->time.current_animation_time >= item->time.display_time) {
      item->time.current_animation_time = 0;
      item->body->rotate(15.0f);
    }
    item->time.current_animation_time +=
      m_timer.returnTime() - item->time.last_timer;
    item->time.last_timer = m_timer.returnTime();
  }
}