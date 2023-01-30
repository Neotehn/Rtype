#include "../../ECS/EntityManager.hpp"
#include "../../ECS/ISystem.hpp"
#include "InputManager/InputManager.hpp"
#include "Systems/CollisionSystem.hpp"
#include "Systems/DisplaySystem.hpp"
#include "Systems/MovementSystem.hpp"
#include "Systems/RandomEnemyGeneratorSystem.hpp"
#include "Systems/ShootingSystem.hpp"

int counter;

EntityManager init() {
  EntityManager entity_manager;

  // background layer 1
  EntityID background1 = entity_manager.createNewEntity();
  entity_manager.Assign<int>(background1, (-272 * 5));
  entity_manager.Assign<float>(background1, 1);
  entity_manager.Assign<sf::Vector2f>(background1, sf::Vector2f(0, 0));
  entity_manager.Assign<SpriteECS>(
      background1, SpriteECS("./sprites/background/bg1.png", {5, 5}));

  // background layer 2
  EntityID background2 = entity_manager.createNewEntity();
  entity_manager.Assign<int>(background2, (-272 * 10));
  entity_manager.Assign<float>(background2, 2);
  entity_manager.Assign<sf::Vector2f>(background2, sf::Vector2f(0, 160));
  entity_manager.Assign<SpriteECS>(
      background2, SpriteECS("./sprites/background/bg2.png", {4, 4}));

  // background layer 3
  EntityID background3 = entity_manager.createNewEntity();
  entity_manager.Assign<int>(background3, (-272 * 5));
  entity_manager.Assign<float>(background3, 3);
  entity_manager.Assign<sf::Vector2f>(background3, sf::Vector2f(0, 0));
  entity_manager.Assign<SpriteECS>(
      background3, SpriteECS("./sprites/background/bg3.png", {5, 5}));

  // player
  EntityID player = entity_manager.createNewEntity();
  SpriteECS player_sprite = SpriteECS("./sprites/starship.png");

  float *player_speed = entity_manager.Assign<float>(player, float(10));
  Pos *player_pos = entity_manager.Assign<Pos>(
      player, Pos{sf::Vector2f(0, 0), sf::Vector2f(300, 300)});

  sf::RectangleShape body;
  body.setSize({200, 200});
  body.setPosition(player_pos->position);
  body.setTexture(player_sprite.getTexture());
  body.setRotation(90.0);
  body.setOutlineColor(sf::Color::Red);
  //body.setOutlineThickness(5);
  sf::RectangleShape *player_body = entity_manager.Assign<sf::RectangleShape>(player, body);
  return entity_manager;
}


int main() {
  EntityManager entity_manager = init();
  std::shared_ptr<EntityManager> entity_manager_ptr =
      std::make_shared<EntityManager>(entity_manager);
  std::vector<std::shared_ptr<ISystem>> systems;

  InputManager input_manager;

  sf::RenderWindow window(sf::VideoMode(800, 800), "R-Type Epitech");
  window.setFramerateLimit(60);

  systems.push_back(
      std::make_shared<DisplaySystem>(entity_manager_ptr, window));
  systems.push_back(std::make_shared<MovementSystem>(entity_manager_ptr));
  systems.push_back(std::make_shared<ShootingSystem>(entity_manager_ptr));
  systems.push_back(
      std::make_shared<RandomEnemyGeneratorSystem>(entity_manager_ptr));
  systems.push_back(std::make_shared<CollisionSystem>(entity_manager_ptr));

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
      input_manager.recordInputs(event);
    }
    SystemData data = {.event_queue = input_manager.getInputs()};

    for (std::shared_ptr<ISystem> system : systems) {
      system->updateData(data);
      system->update();
    }

  }
  return 0;
}
