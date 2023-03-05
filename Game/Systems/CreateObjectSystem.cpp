#include "CreateObjectSystem.hpp"

CreateObjectSystem::CreateObjectSystem(
  std::shared_ptr<EntityManager> t_em,
  std::vector<SoundSystem::SoundType> &t_sounds,
  rtype::IGraphicLoader *t_graphic_loader, const std::string &t_path_to_sprite)
    : m_play_sounds(t_sounds) {
  m_em = t_em;
  m_graphic_loader = t_graphic_loader;
  m_path_to_sprite = t_path_to_sprite;
}

void CreateObjectSystem::updateData(SystemData &t_data) {
  m_event_queue = t_data.event_queue;
}

void CreateObjectSystem::update() {
  for (std::shared_ptr<Action> action :
       m_event_queue.getAllOfType(Action::ActionType::CREATE)) {
    Action::ObjectType type = action->getCreateType();
    EntityID id = action->getId();
    rtype::Vector2f pos = action->getCreatePosition();
    float velocity;
    int player_id = action->getClientId();
    switch (type) {
      case Action::ObjectType::PLAYER:
        initPlayerClient(id, m_path_to_sprite, pos, m_em, m_graphic_loader,
                         player_id);
        break;
      case Action::ObjectType::BULLET:
        m_play_sounds.push_back(SoundSystem::SoundType::shoot);
        initBulletClient(id, pos, action, m_em, m_graphic_loader,
                         action->getCollisionPartnerId());
        break;
      case Action::ObjectType::ENEMY:
        velocity = action->getVelocity();
        std::cout << "Create enemy at pos " << pos.x << " " << pos.y << " "
                  << velocity << std::endl;
        initEnemyClient(id, pos, velocity, m_em, m_graphic_loader);
        break;
      case Action::ObjectType::PAYWALL:
        initPayWallClient(id, m_em, m_graphic_loader);
        break;
      case Action::ObjectType::ENDBOSS:
        initEndbossClient(id, m_em, m_graphic_loader);
        break;
      case Action::ObjectType::EXPLOSION:
        m_play_sounds.push_back(SoundSystem::SoundType::explosion);
        initExplosionClient(id, pos, m_em, m_graphic_loader);
        break;
      case Action::ObjectType::POWER_UP:
        initPowerUpClient(id, pos, m_em, m_graphic_loader);
        break;
      case Action::ObjectType::ITEM:
        initItemClient(id, rtype::ItemType(action->getItemType()), pos, m_em,
                       m_graphic_loader);
        break;
      case Action::ObjectType::OBSTACLE:
        initObstacleClient(m_em, m_graphic_loader, pos,
                           action->getCreateSpritePath(),
                           action->getTotalObstacleWidth(), id);
        break;
      default:
        break;
    }
  }
}