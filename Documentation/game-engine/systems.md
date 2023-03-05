# Systems

To display and handle events for our game we implemented different systems, that have each a special function.

Following systems are implemented:

* [AnimationSystem](../systems/animationsystem.md)
* [CollisionSystem](../systems/collisionsystem.md)
* [CreateObjectSystem](../systems/createobjectsystem.md)
* [CreatePlayerSystem](../systems/createplayersystem.md)
* [DamageSystem](../systems/damagesystem.md)
* [DestroySystem](../systems/destroysystem.md)
* [DisplaySystem](../systems/displaysystem.md)
* [GUISystem](../systems/guisystem.md)
* [MovementSystem](../systems/movementsystem.md)
* [PowerUpSystem](../systems/powerupsystem.md)
* [RandomEnemyGeneratorSystem](../systems/randomenemygeneratorsystem.md)
* [ShootingSystem](../systems/shootingsystem.md)
* [SoundSystem](../systems/soundsystem.md)

The GameState contains a vector that contains all different systems and in the update function of the GameState the systems get updated and excecuted.

In case you want to add a system of your own, create your files under "Game/Systems/" with the naming conversion "{Name}System", where "{Name}" stands for the name of your system.

Your system needs to inherit from "ISystem" and contain an override for an "updateData" and "update" function.

NameSystem.hpp:

```
#ifndef NAMESYSTEM_HPP_
#define NAMESYSTEM_HPP_

#include "../ECS/ISystem.hpp"
#include "../ECS/DataTypesECS.hpp" //add needed include files here

class NameSystem : public ISystem {
 public:
  NameSystem(std::shared_ptr<EntityManager> t_em); // add needed arguments
  ~NameSystem() = default;

  void update() override;
  void updateData(SystemData &t_data) override;

 private:
  // add needed variables here
};

#endif  // CLIENT_SRC_SYSTEMS_COLLISIONSYSTEM_HPP_
```

NameSystem.cpp:

```
#include "NameSystem.hpp"

NameSystem::NameSystem(std::shared_ptr<EntityManager> t_em) {
  m_em = t_em;
}

void NameSystem::updateData(SystemData &t_data) {} // update entity manager if needed

void NameSystem::update() {
  // excecution of your functions
}

```

Once you finished your system go in the "GameState.hpp" and add your hpp file to the include and in the "GameState.cpp" add following line to the "initSystems()" function:

```
systems.push_back(std::make_shared<NameSystem>(m_em));
```

Depending on if your system is relevant to the server add it in the first block of the if statement, if it is only relevant for the client to the second block and if it is relevant for both add it below the if statement.
