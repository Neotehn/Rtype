#include "DamageSystem.hpp"

DamageSystem::DamageSystem(std::shared_ptr<EntityManager> t_em) { m_em = t_em; }

DamageSystem::~DamageSystem() {}

void DamageSystem::update() {
  for (std::shared_ptr<Action> action :
       m_event_queue.getAllOfType(Action::ActionType::DAMAGE)) {
    for (EntityID healthbar :
         EntityViewer<float, Health, Pos, sf::RectangleShape>(*m_em.get())) {
      Health *health = (*m_em.get()).Get<Health>(healthbar);
      int current_health = health->healthbar.getHealth();
      int damage = action->getShootDamage();

      if (current_health - damage < 0) { return; }
      health->healthbar.setHealth(current_health - damage);

      SpriteECS health_new_bar = SpriteECS(
        health->healthbar.getSpritesPaths()[health->healthbar.getHealth()]);

      health->body.setTexture(health_new_bar.getTexture());
    }
  }
}

void DamageSystem::updateData(SystemData &t_data) {
  m_event_queue = t_data.event_queue;
}
