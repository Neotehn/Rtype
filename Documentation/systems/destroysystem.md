# DestroySystem

If the DESTROY command gets send, this system will destroy the specified entity.

DestroySystem.hpp:

```
#ifndef CLIENT_SRC_SYSTEMS_DESTROYSYSTEM_HPP_
#define CLIENT_SRC_SYSTEMS_DESTROYSYSTEM_HPP_

#include <string>
#include <memory>

#include "../ECS/DataTypesECS.hpp"
#include "../ECS/ISystem.hpp"
#include "../../Client/src/Action/Action.hpp"

class DestroySystem : public ISystem {
 public:
  DestroySystem(std::shared_ptr<EntityManager> t_em);
  ~DestroySystem() = default;

  virtual void update() override;
  virtual void updateData(SystemData &t_data) override;

 private:
  EventQueue m_event_queue;
};

#endif  // CLIENT_SRC_SYSTEMS_DESTROYSYSTEM_HPP_
```

DestroySystem.cpp:

```
#include "DestroySystem.hpp"

DestroySystem::DestroySystem(std::shared_ptr<EntityManager> t_em) {
  m_em = t_em;
}

void DestroySystem::update() {
  for (std::shared_ptr<Action> action :
       m_event_queue.getAllOfType(Action::ActionType::DESTROY)) {
    for (EntityID enemy_ent : EntityViewer<>(*m_em)) {
      if (enemy_ent == action->getId()) {
        std::cout << "gonna destroy entity " << enemy_ent << std::endl;
        m_em->destroyEntity(enemy_ent);
        std::cout << "destroyed entity " << enemy_ent << std::endl;
      }
    }
  }
}

void DestroySystem::updateData(SystemData &t_data) {
  m_event_queue = t_data.event_queue;
}
```

[Back](../game-engine/systems.md)
