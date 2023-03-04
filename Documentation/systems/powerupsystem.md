# PowerUpSystem

The PowerUpSystem will handle all power ups like health increase or damage boost.

PowerUpSystem.hpp:

```
#ifndef R_TYPE_CLIENT_POWERUPSYSTEM_HPP
#define R_TYPE_CLIENT_POWERUPSYSTEM_HPP

#include <memory>

#include "../ECS/ISystem.hpp"
#include "./SoundSystem.hpp"

class PowerUpSystem : public ISystem {
 public:
  PowerUpSystem(std::shared_ptr<EntityManager> t_em,
                std::vector<SoundSystem::SoundType> &t_sounds,
                rtype::IGraphicLoader *t_graphic_loader);
  ~PowerUpSystem() = default;

  void update() override;
  void updateData(SystemData &t_data) override;

 private:
  EventQueue m_event_queue;
  std::vector<SoundSystem::SoundType> &m_play_sounds;
  rtype::IGraphicLoader *m_graphic_loader;

  void increaseHealth(std::shared_ptr<Action> action, Player *t_player);
};

#endif  //R_TYPE_CLIENT_POWERUPSYSTEM_HPP
```

PowerUpSystem.cpp:

```
#include "PowerUpSystem.hpp"

PowerUpSystem::PowerUpSystem(std::shared_ptr<EntityManager> t_em,
                             std::vector<SoundSystem::SoundType> &t_sounds,
                             rtype::IGraphicLoader *t_graphic_loader)
    : m_play_sounds(t_sounds) {
  m_em = t_em;
  m_graphic_loader = t_graphic_loader;
}

void PowerUpSystem::updateData(SystemData &t_data) {
  m_event_queue = t_data.event_queue;
}

void PowerUpSystem::update() {
  for (std::shared_ptr<Action> action :
       m_event_queue.getAllOfType(Action::ActionType::INCREASE)) {
    for (EntityID ent : EntityViewer<Player>(*m_em)) {
      if (ent != action->getId()) continue;
      Action::IncreaseType type = action->getIncreaseType();
      Player *player = (*m_em).Get<Player>(ent);

      switch (type) {
        case Action::IncreaseType::LIFE:
          increaseHealth(action, player);
          m_play_sounds.push_back(SoundSystem::SoundType::power_up);
          break;
        case Action::IncreaseType::KILLS:
          player->kills += 1;
          player->exp += action->getIncreaseValue();
          break;
        case Action::IncreaseType::FIRE_SHOT:
          player->fire_shot += action->getIncreaseValue();
          break;
        case Action::IncreaseType::BOMB_SHOT:
          player->bomb_shot += action->getIncreaseValue();
          break;
        case Action::IncreaseType::SPEED:
          player->speed += action->getIncreaseValue();
          break;
        case Action::IncreaseType::COINS:
          player->coins += 1;
          player->coin_shot += action->getIncreaseValue();
          break;
        default:
          break;
      }
    }
  }
}

void PowerUpSystem::increaseHealth(std::shared_ptr<Action> action,
                                   Player *t_player) {
  if (t_player->health.healthbar.getHealth() < 3) {
    t_player->health.healthbar.setHealth(
      t_player->health.healthbar.getHealth() + 1);
  }
  SpriteECS health_new_bar =
    SpriteECS(t_player->health.healthbar
                .getSpritesPaths()[t_player->health.healthbar.getHealth()],
              m_graphic_loader);

  t_player->health.body->setTexture(health_new_bar.getTexture());
}
```

[Back](../game-engine/systems.md)
