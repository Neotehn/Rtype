# CreateObjectSystem

Depending on the transmitted [ActionType](../overview/protocol.md), this system will create the entities. For example if the CREATE command gets send, the system will create the appropiate entity definded by the following arguments of the CREATE command.

CreateObjectSystem.hpp:

```
#ifndef R_TYPE_CLIENT_CREATEOBJECTSYSTEM_HPP
#define R_TYPE_CLIENT_CREATEOBJECTSYSTEM_HPP

#include <memory>
#include <string>

#include "../CreateEntities/Init.hpp"
#include "../ECS/ISystem.hpp"
#include "../ECS/DataTypesECS.hpp"
#include "./AnimationSystem.hpp"
#include "./SoundSystem.hpp"

class CreateObjectSystem : public ISystem {
 public:
  CreateObjectSystem(std::shared_ptr<EntityManager> t_em,
                     std::vector<SoundSystem::SoundType> &t_sounds,
                     rtype::IGraphicLoader *t_graphic_loader,
                     const std::string &t_path_to_sprite);
  ~CreateObjectSystem() = default;

  void update() override;
  void updateData(SystemData &t_data) override;

 private:
  std::shared_ptr<EntityManager> m_em;
  EventQueue m_event_queue;
  std::vector<SoundSystem::SoundType> &m_play_sounds;
  rtype::IGraphicLoader *m_graphic_loader;
  std::string m_path_to_sprite;
};

#endif  //R_TYPE_CLIENT_CREATEOBJECTSYSTEM_HPP
```

CreateObjectSystem.cpp:

```
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
```

[Back](../game-engine/systems.md)
