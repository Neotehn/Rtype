#ifndef GAME_GAME_HPP
#define GAME_GAME_HPP

#include <memory>
#include <vector>

#include "./ECS/EntityManager.hpp"
#include "./ECS/DataTypesECS.hpp"
#include "./ECS/ISystem.hpp"
#include "./Systems/AnimationSystem.hpp"
#include "./Systems/CollisionSystem.hpp"
#include "./Systems/DisplaySystem.hpp"
#include "./Systems/MovementSystem.hpp"
#include "./Systems/RandomEnemyGeneratorSystem.hpp"
#include "./Systems/ShootingSystem.hpp"
#include "../Client/src/InputManager/InputManager.hpp"

class Game {
 public:
  Game();
  ~Game();

  void run();

 private:
  sf::RenderWindow m_window;
  InputManager m_input_manager;

  EntityManager initEntityManager();
  std::vector<std::shared_ptr<ISystem>>
    initSystems(std::shared_ptr<EntityManager>);
};

#endif  //GAME_GAME_HPP
