#include <iostream>
#include "Player.h"
#include "SFML/Graphics.hpp"

void setBackgroundScale(const sf::Vector2u& textureSize,
                        const sf::Vector2u& windowSize, float scaleX,
                        float scaleY, sf::Sprite& background);
int main() {
  Player player("./sprites/starship.png");
  sf::Texture backgroundTexture;

  if (!backgroundTexture.loadFromFile("./sprites/background2.jpg"))
    std::cerr << "Error loading background texture" << std::endl;
  sf::Sprite background(backgroundTexture);
  sf::RenderWindow window(sf::VideoMode(800, 1400), "R-Type Epitech");
  sf::Vector2f windowSize =sf::Vector2f (window.getSize().x, window.getSize().y);
  window.setFramerateLimit(60);
  float playerX = player.getPosition().x;
  background.setPosition(sf::Vector2f(-(playerX * 0.1), 0));
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
    player.update();
    player.display(window);
    window.display();
  }
  return 0;
}
void setBackgroundScale(const sf::Vector2u& textureSize,
                        const sf::Vector2u& windowSize, float scaleX,
                        float scaleY, sf::Sprite& background) {
  scaleX = (float) windowSize.x / textureSize.x;
  scaleY = (float) windowSize.y / textureSize.y;
  background.setScale(scaleX, scaleY);
}
