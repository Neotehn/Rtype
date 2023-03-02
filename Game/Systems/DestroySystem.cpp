#include "DestroySystem.hpp"

DestroySystem::DestroySystem(std::shared_ptr<EntityManager> t_em) {
  m_em = t_em;
}

void DestroySystem::update() {
  for (std::shared_ptr<Action> action :
       m_event_queue.getAllOfType(Action::ActionType::DESTROY)) {
    for (EntityID enemy_ent : EntityViewer<>(*m_em)) {
      if (enemy_ent == action->getId()) {
        std::cout << "gonna destroy entity " << enemy_ent << std::endl;
        m_em->destroyEntity(enemy_ent);
        std::cout << "destroyed entity " << enemy_ent << std::endl;
      }
    }
  }
}

void DestroySystem::updateData(SystemData &t_data) {
  m_event_queue = t_data.event_queue;
}
