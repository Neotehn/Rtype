#include "PowerUpSystem.hpp"

PowerUpSystem::PowerUpSystem(std::shared_ptr<EntityManager> t_em,
                             std::vector<SoundSystem::SoundType> &t_sounds)
    : m_play_sounds(t_sounds) {
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
    Player *player;

    switch (type) {
      case Action::IncreaseType::LIFE:
        increaseHealth(action);
        m_play_sounds.push_back(SoundSystem::SoundType::power_up);
        break;
      case Action::IncreaseType::FIRE_SHOT:
        player = (*m_em.get()).Get<Player>(action->getId());
        player->fire_shot += action->getIncreaseValue();
        break;
      case Action::IncreaseType::BOMB_SHOT:
        player = (*m_em.get()).Get<Player>(action->getId());
        player->bomb_shot += action->getIncreaseValue();
        break;
      case Action::IncreaseType::SPEED:
        player = (*m_em.get()).Get<Player>(action->getId());
        player->speed += action->getIncreaseValue();
        break;
      case Action::IncreaseType::COINS:
        player = (*m_em.get()).Get<Player>(action->getId());
        player->coins += action->getIncreaseValue();
        break;
      default:
        break;
    }
  }
}

void PowerUpSystem::increaseHealth(std::shared_ptr<Action> action) {
  Player *player = (*m_em.get()).Get<Player>(action->getId());
  if (player->health.healthbar.getHealth() < 3) {
    player->health.healthbar.setHealth(player->health.healthbar.getHealth() +
                                       1);
  }
  SpriteECS health_new_bar =
    SpriteECS(player->health.healthbar
                .getSpritesPaths()[player->health.healthbar.getHealth()]);

  player->health.body->setTexture(health_new_bar.getTexture());
}
