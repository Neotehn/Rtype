#include "DamageSystem.hpp"

DamageSystem::DamageSystem(std::shared_ptr<EntityManager> t_em,
                           InputManager &t_client_input_manager,
                           std::size_t t_port_number, bool &t_is_running)
    : m_client_input_manager(t_client_input_manager),
      m_is_running(t_is_running) {
  m_em = t_em;
  m_port_number = t_port_number;
}

DamageSystem::~DamageSystem() {}

void DamageSystem::update() {
  for (std::shared_ptr<Action> action :
       m_event_queue.getAllOfType(Action::ActionType::DAMAGE)) {
    for (EntityID healthbar :
         EntityViewer<float, Health, Pos, sf::RectangleShape>(*m_em.get())) {
      Health *health = (*m_em.get()).Get<Health>(healthbar);
      int current_health = health->healthbar.getHealth();
      int damage = action->getShootDamage();
      int new_health = current_health - damage;

      if (new_health < 0) { return; }
      if (new_health == 0) {
        std::cout << "player died" << std::endl;
        m_is_running = false;
        m_client_input_manager.addActionsToQueue(std::make_shared<Action>(
          StateAction(Action::ActionType::END, m_port_number)));
      }
      health->healthbar.setHealth(new_health);

      SpriteECS health_new_bar = SpriteECS(
        health->healthbar.getSpritesPaths()[health->healthbar.getHealth()]);

      health->body.setTexture(health_new_bar.getTexture());
    }
  }
}

void DamageSystem::updateData(SystemData &t_data) {
  m_event_queue = t_data.event_queue;
}
