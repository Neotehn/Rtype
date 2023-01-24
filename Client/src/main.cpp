#include "../../ECS/EntityManager.hpp"
#include "../../ECS/EntityViewer.hpp"
#include "Player.hpp"

int main() {
  //Player player("./sprites/starship.png");
  sf::Texture background_texture;

  EntityManager entity_manager;
  EntityID player = entity_manager.createNewEntity();
  Pos *player_pos = entity_manager.Assign<Pos>(player, Pos({{0, 0}, {300, 300}}));
  SpriteECS *player_sprite = entity_manager.Assign<SpriteECS>(player, SpriteECS("./sprites/starship.png"));
  float *player_speed = entity_manager.Assign<float>(player, float(10));

  sf::RenderWindow window(sf::VideoMode(800, 1400), "R-Type Epitech");
  sf::Vector2f window_size =
      sf::Vector2f(window.getSize().x, window.getSize().y);
  window.setFramerateLimit(60);
  //float player_x = player.getPosition().x;

  if (!background_texture.loadFromFile("./sprites/background2.jpg"))
    std::cerr << "Error loading background texture" << std::endl;
  sf::Sprite background(background_texture);
  //background.setPosition(sf::Vector2f(-float(player_x * 0.1), 0));

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
      if (event.type == sf::Event::KeyPressed) {
        //player.handlePlayerInput(event);
      }
    }
    window.clear();
    background.move(-0.1f, 0.0f);
    for (EntityID ent : EntityViewer<Pos, SpriteECS>(entity_manager))
    {
      Pos* player_pos = entity_manager.Get<Pos>(ent);
      SpriteECS* player_sprite = entity_manager.Get<SpriteECS>(ent);
      window.draw(player_sprite->getSprite());
    }

    window.draw(background);
    window.display();
  }
  return 0;
}
