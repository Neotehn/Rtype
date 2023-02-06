#include "DamageSystem.hpp"

DamageSystem::DamageSystem(std::shared_ptr<EntityManager> t_em) { m_em = t_em; }

DamageSystem::~DamageSystem() {}

void DamageSystem::update() {
  for (std::shared_ptr<Action> action :
       m_event_queue.getAllOfType(Action::ActionType::COLLISION)) {
    for (EntityID healthbar :
         EntityViewer<HealthBar, Pos, sf::RectangleShape, std::size_t>(
           *m_em.get())) {
      sf::RectangleShape *body =
        (*m_em.get()).Get<sf::RectangleShape>(healthbar);
      HealthBar *bar = (*m_em.get()).Get<HealthBar>(healthbar);
      std::size_t current_health = bar->getHealth();

      if (current_health <= 0) { break; }
      bar->setHealth(current_health - 1);

      SpriteECS health_new_bar =
        SpriteECS(bar->getSpritesPaths()[bar->getHealth()]);

      body->setTexture(health_new_bar.getTexture());
    }
    EntityID id = action->getId();
    m_em->destroyEntity(id);
  }
}

void DamageSystem::updateData(SystemData &t_data) {
  m_event_queue = t_data.event_queue;
}
