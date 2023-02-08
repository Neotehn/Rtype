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
  for (EntityID ent : EntityViewer<std::string, Pos, sf::RectangleShape,
                                   AnimationTime, AnimationRect>(*m_em.get())) {
    AnimationTime *time = (*m_em.get()).Get<AnimationTime>(ent);
    AnimationRect *anim_rect = (*m_em.get()).Get<AnimationRect>(ent);

    if (time->last_timer == 0) { time->last_timer = m_timer.returnTime(); }
    if (time->current_animation_time >= time->display_time) {
      time->current_animation_time = 0;
      sf::RectangleShape *shape = (*m_em.get()).Get<sf::RectangleShape>(ent);
      sf::IntRect rect = shape->getTextureRect();
      if (rect.left >= anim_rect->limit) {
        std::string *type = (*m_em.get()).Get<std::string>(ent);
        if (*type == "explosion") {
          m_input_manager.addActionsToQueue(
            std::make_shared<Action>(DestroyAction(ent)));
        } else {
          rect.left = 0;
        }
      } else {
        rect.left += anim_rect->size;
      }
      shape->setTextureRect(rect);
    }
    time->current_animation_time += m_timer.returnTime() - time->last_timer;
    time->last_timer = m_timer.returnTime();
  }
}
