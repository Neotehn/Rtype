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
}

void DestroySystem::updateData(SystemData &t_data) {
  m_event_queue = t_data.event_queue;
}
