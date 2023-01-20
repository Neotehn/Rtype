#include "Player.hpp"

int main() {
  Player player("./sprites/starship.png");
  sf::Texture backgroundTexture;

  sf::RenderWindow window(sf::VideoMode(800, 1400),
                          "R-Type Epitech");
  sf::Vector2f windowSize =
      sf::Vector2f(window.getSize().x, window.getSize().y);
  window.setFramerateLimit(60);
  float playerX = player.getPosition().x;

  if (!backgroundTexture.loadFromFile("./sprites/background2.jpg"))
    std::cerr << "Error loading background texture" << std::endl;
  sf::Sprite background(backgroundTexture);
  background.setPosition(sf::Vector2f(-float(playerX * 0.1), 0));

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
      if (event.type == sf::Event::KeyPressed) {
        player.handlePlayerInput(event);
      }
    }
    window.clear();
    player.update(windowSize);
    background.move(-0.1f, 0.0f);
    window.draw(background);
    player.display(window);
    window.display();
  }
  return 0;
}
