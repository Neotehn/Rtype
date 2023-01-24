#include "../../ECS/EntityManager.hpp"
#include "../../ECS/EntityViewer.hpp"
#include "Player.hpp"

int counter;

EntityManager init() {
  EntityManager entity_manager;

  EntityID background = entity_manager.createNewEntity();
  SpriteECS *background_sprite = entity_manager.Assign<SpriteECS>(background, SpriteECS("./sprites/background2.jpg"));

  EntityID player = entity_manager.createNewEntity();
  Pos *player_pos = entity_manager.Assign<Pos>(player, Pos({{0, 0}, {300, 300}}));
  SpriteECS *player_sprite = entity_manager.Assign<SpriteECS>(player, SpriteECS("./sprites/starship.png"));
  float *player_speed = entity_manager.Assign<float>(player, float(10));

  return entity_manager;
}


int main() {
  EntityManager entity_manager = init();


  sf::RenderWindow window(sf::VideoMode(800, 1400), "R-Type Epitech");
  window.setFramerateLimit(60);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
      if (event.type == sf::Event::KeyPressed) {
        //player.handlePlayerInput(event);
      }
    }
    window.clear();
    //background.move(-0.1f, 0.0f);


    for ( EntityID ent : EntityViewer<Pos, SpriteECS, float>(entity_manager))
    {
      printf("Entity %d has a position and a sprite and speed\n", GetEntityIndex(ent));
        float* player_speed = entity_manager.Get<float>(ent);
        std::cout << "Player speed: " << *player_speed << std::endl;
    }

    for (EntityID ent : EntityViewer<SpriteECS>(entity_manager))
    {
      printf("Entity(SPRITE) %d has a sprite\n", GetEntityIndex(ent));
      SpriteECS* sprite = entity_manager.Get<SpriteECS>(ent);
      window.draw(*(sprite)->getSprite());
    }
    window.display();
  }
  return 0;
}
