#include <iostream>

#include "./gameEngine/inc/Menu.hpp"

int main() {
  Menu window(sf::VideoMode(1920, 1080));
  window.runMenu();
  return 0;
}
