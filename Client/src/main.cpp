#include <iostream>

#include "Player.h"
#include "SFML/Graphics.hpp"

int main() {
  Player player("./sprites/starship.png");
  sf::RenderWindow window(sf::VideoMode(800, 1400), "R-Type Epitech");

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
      if (event.type == sf::Event::KeyPressed) {
        player.handlePlayerInput(event);
      }
    }
    window.clear();
    player.display(window);
    window.display();
  }
  return 0;
}
