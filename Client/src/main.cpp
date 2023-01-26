#include "../../ECS/EntityManager.hpp"
#include "../../ECS/ISystem.hpp"
#include "InputManager/InputManager.hpp"
#include "Systems/DisplaySystem.hpp"
#include "Systems/MovementSystem.hpp"


int counter;

EntityManager init() {
  EntityManager entity_manager;

  EntityID background = entity_manager.createNewEntity();
  SpriteECS *background_sprite = entity_manager.Assign<SpriteECS>(background, SpriteECS("./sprites/background2.jpg"));

  EntityID player = entity_manager.createNewEntity();
  SpriteECS player_sprite = SpriteECS("./sprites/starship.png");

  float *player_speed = entity_manager.Assign<float>(player, float(10));
  Pos *player_pos = entity_manager.Assign<Pos>(player, Pos{ sf::Vector2f(0, 0), sf::Vector2f(300, 300)});

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
  std::vector<std::shared_ptr<ISystem>> systems;

  InputManager input_manager;

  sf::RenderWindow window(sf::VideoMode(800, 800), "R-Type Epitech");
  window.setFramerateLimit(60);

  systems.push_back(std::make_shared<DisplaySystem>(std::make_shared<EntityManager>(entity_manager), window));
  systems.push_back(std::make_shared<MovementSystem>(std::make_shared<EntityManager>(entity_manager)));

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
      input_manager.recordInputs(event);

    }
    SystemData data = {.event_queue= input_manager.getInputs()};

    for (std::shared_ptr<ISystem> system : systems) {
      system->updateData(data);
      system->update();
    }

  }
  return 0;
}
