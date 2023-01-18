#include <iostream>

#include "SFML/Graphics.hpp"
#include "Player.h"

int main() {
  Player player("./sprites/starship.png");
  sf::RenderWindow window(sf::VideoMode(800, 1400), "SFML works!");

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }
    window.clear();
    player.display(window);
    window.display();
  }
  return 0;
}
