#include "DestroySystem.hpp"

DestroySystem::DestroySystem(std::shared_ptr<EntityManager> t_em) {
  m_em = t_em;
}

DestroySystem::~DestroySystem() {}

void DestroySystem::update() {
  for (std::shared_ptr<Action> action :
       m_event_queue.getAllOfType(Action::ActionType::DESTROY)) {
    EntityID id = action->getId();
    m_em->destroyEntity(id);
  }
  for (EntityID ent : EntityViewer<std::string, Pos, sf::RectangleShape,
                                   AnimationTime, AnimationRect>(*m_em.get())) {
    std::string *type = (*m_em.get()).Get<std::string>(ent);
    if (*type == "explosion") {
      AnimationRect *anim_rect = (*m_em.get()).Get<AnimationRect>(ent);
      if (anim_rect->has_been_reset) { m_em->destroyEntity(ent); }
    }
  }
}

void DestroySystem::updateData(SystemData &t_data) {
  m_event_queue = t_data.event_queue;
}
