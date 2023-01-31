#include "Player.hpp"

int main() {
  Player player("./sprites/starship.png");
  sf::Texture background_texture;

  sf::RenderWindow window(sf::VideoMode(800, 1400), "R-Type Epitech");
  sf::Vector2f window_size =
    sf::Vector2f(window.getSize().x, window.getSize().y);
  window.setFramerateLimit(60);
  float player_x = player.getPosition().x;

  if (!background_texture.loadFromFile("./sprites/background2.jpg"))
    std::cerr << "Error loading background texture" << std::endl;
  sf::Sprite background(background_texture);
  background.setPosition(sf::Vector2f(-float(player_x * 0.1), 0));

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) { window.close(); }
      if (event.type == sf::Event::KeyPressed) {
        player.handlePlayerInput(event);
      }
    }
    window.clear();
    player.update(window_size);
    background.move(-0.1f, 0.0f);
    window.draw(background);
    player.display(window);
    window.display();
  }
  return 0;
}
