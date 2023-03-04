# DamageSystem

The DamageSystem checks if the player got hit and updates the players health.

DamageSystem.hpp:

```
#ifndef CLIENT_SRC_SYSTEMS_DAMAGESYSTEM_HPP_
#define CLIENT_SRC_SYSTEMS_DAMAGESYSTEM_HPP_

#include <string>
#include <memory>

#include "../ECS/DataTypesECS.hpp"
#include "../ECS/ISystem.hpp"
#include "../../Client/src/Action/Action.hpp"
#include "../../Client/src/Action/StateAction.hpp"
#include "../../Client/src/InputManager/InputManager.hpp"
#include "./SoundSystem.hpp"

class DamageSystem : public ISystem {
 public:
  DamageSystem(std::shared_ptr<EntityManager> t_em,
               InputManager &t_client_input_manager, std::size_t t_port_number,
               bool &t_is_running,
               std::vector<SoundSystem::SoundType> &t_sounds,
               rtype::IGraphicLoader *t_graphic_loader);
  ~DamageSystem() = default;

  virtual void update() override;
  virtual void updateData(SystemData &t_data) override;

 private:
  EventQueue m_event_queue;
  InputManager &m_client_input_manager;
  std::size_t m_port_number;
  bool &m_is_running;
  std::vector<SoundSystem::SoundType> &m_play_sounds;
  rtype::IGraphicLoader *m_graphic_loader;
};

#endif  // CLIENT_SRC_SYSTEMS_DAMAGESYSTEM_HPP_

```

DamageSystem.cpp:

```
#include "DamageSystem.hpp"

DamageSystem::DamageSystem(std::shared_ptr<EntityManager> t_em,
                           InputManager &t_client_input_manager,
                           std::size_t t_port_number, bool &t_is_running,
                           std::vector<SoundSystem::SoundType> &t_sounds,
                           rtype::IGraphicLoader *t_graphic_loader)
    : m_client_input_manager(t_client_input_manager),
      m_is_running(t_is_running), m_play_sounds(t_sounds) {
  m_em = t_em;
  m_port_number = t_port_number;
  m_graphic_loader = t_graphic_loader;
}

void DamageSystem::update() {
  for (std::shared_ptr<Action> action :
       m_event_queue.getAllOfType(Action::ActionType::DAMAGE)) {
    for (EntityID player_id : EntityViewer<Player>(*m_em)) {
      if (player_id != action->getCollisionPartnerId()) { continue; }
      Player *player = (*m_em).Get<Player>(player_id);
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
                    .getSpritesPaths()[player->health.healthbar.getHealth()],
                  m_graphic_loader);

      player->health.body->setTexture(health_new_bar.getTexture());
    }
    for (EntityID enemy_id : EntityViewer<Enemy>(*m_em)) {
      if (enemy_id != action->getCollisionPartnerId()) { continue; }
      Enemy *enemy = (*m_em).Get<Enemy>(enemy_id);
      enemy->health.cur_health -= action->getShootDamage();

      if (enemy->health.cur_health <= 0) {
        std::cout << "Enemy died :)" << std::endl;
        m_play_sounds.push_back(SoundSystem::SoundType::death);
      }
      float x_size =
        (float(enemy->health.cur_health) / float(enemy->health.max_health)) *
        100.0;
      enemy->health.left_health->setSize(
        {x_size, enemy->health.left_health->getSize().y});
    }
  }
}

void DamageSystem::updateData(SystemData &t_data) {
  m_event_queue = t_data.event_queue;
}
```

[Back](../game-engine/systems.md)
