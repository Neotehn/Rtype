#include "CreateObjectSystem.hpp"

CreateObjectSystem::CreateObjectSystem(
  std::shared_ptr<EntityManager> t_em,
  std::vector<SoundSystem::SoundType> &t_sounds,
  rtype::IGraphicLoader *t_graphic_loader)
    : m_play_sounds(t_sounds) {
  m_em = t_em;
  m_graphic_loader = t_graphic_loader;
}

CreateObjectSystem::~CreateObjectSystem() {}

void CreateObjectSystem::updateData(SystemData &t_data) {
  m_event_queue = t_data.event_queue;
}

void CreateObjectSystem::update() {
  for (std::shared_ptr<Action> action :
       m_event_queue.getAllOfType(Action::ActionType::CREATE)) {
    Action::ObjectType type = action->getCreateType();
    EntityID id = action->getId();
    rtype::Vector2f pos = action->getCreatePosition();
    float velocity = 0;
    int player_id = action->getClientId();
    switch (type) {
      case Action::ObjectType::PLAYER:
        initPlayerClient(id, action->getCreateSpritePath(), pos, m_em,
                         m_graphic_loader, player_id);
        break;
      case Action::ObjectType::BULLET:
        m_play_sounds.push_back(SoundSystem::SoundType::shoot);
        initBulletClient(id, pos, action->getShootType(), m_em,
                         m_graphic_loader, action->getCollisionPartnerId());
        break;
      case Action::ObjectType::ENEMY:
        velocity = action->getVelocity();
        std::cout << "Create enemy at pos " << pos.x << " " << pos.y << " "
                  << velocity << std::endl;
        initEnemyClient(id, pos, velocity, m_em, m_graphic_loader);
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
      default:
        break;
    }
  }
}