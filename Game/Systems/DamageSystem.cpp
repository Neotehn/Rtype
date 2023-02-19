#include "DamageSystem.hpp"

DamageSystem::DamageSystem(std::shared_ptr<EntityManager> t_em,
                           InputManager &t_client_input_manager,
                           std::size_t t_port_number, bool &t_is_running,
                           std::vector<SoundSystem::SoundType> &t_sounds)
    : m_client_input_manager(t_client_input_manager),
      m_is_running(t_is_running), m_play_sounds(t_sounds) {
  m_em = t_em;
  m_port_number = t_port_number;
}

DamageSystem::~DamageSystem() {}

void DamageSystem::update() {
  for (std::shared_ptr<Action> action :
       m_event_queue.getAllOfType(Action::ActionType::DAMAGE)) {
    for (EntityID player_id : EntityViewer<Player>(*m_em.get())) {
      Player *player = (*m_em.get()).Get<Player>(player_id);
      int current_health = player->health.healthbar.getHealth();
      int damage = action->getShootDamage();
      int new_health = current_health - damage;

      if (new_health < 0) { return; }
      if (new_health == 0) {
        std::cout << "Player died :(" << std::endl;
        m_play_sounds.push_back(SoundSystem::SoundType::death);
        m_client_input_manager.addActionsToQueue(std::make_shared<Action>(
          StateAction(Action::ActionType::END, m_port_number)));
      }
      player->health.healthbar.setHealth(new_health);

      SpriteECS health_new_bar =
        SpriteECS(player->health.healthbar
                    .getSpritesPaths()[player->health.healthbar.getHealth()]);

      player->health.body->setTexture(health_new_bar.getTexture());
    }
  }
}

void DamageSystem::updateData(SystemData &t_data) {
  m_event_queue = t_data.event_queue;
}
