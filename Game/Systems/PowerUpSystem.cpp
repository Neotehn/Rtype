#include "PowerUpSystem.hpp"

PowerUpSystem::PowerUpSystem(std::shared_ptr<EntityManager> t_em) {
  m_em = t_em;
}

PowerUpSystem::~PowerUpSystem() {}

void PowerUpSystem::updateData(SystemData &t_data) {
  m_event_queue = t_data.event_queue;
}

void PowerUpSystem::update() {
  for (std::shared_ptr<Action> action :
       m_event_queue.getAllOfType(Action::ActionType::INCREASE)) {
    Action::IncreaseType type = action->getIncreaseType();
    HealthBar *health_bar;

    switch (type) {
      case Action::IncreaseType::LIFE:
        std::cout << "increase player health" << std::endl;

        //        health_bar = (*m_em.get()).Get<HealthBar>(action->getId());
        //        if (health_bar->getHealth() < 3) {
        //          health_bar->setHealth(health_bar->getHealth() + 1);
        //        }
        break;
      default:
        break;
    }
  }
}
