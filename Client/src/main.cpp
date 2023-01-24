#include <iostream>

#include "./gameEngine/inc/Core.hpp"

int main() {
  Core core(sf::VideoMode(1280, 720));
  core.loop();
  return 0;
}
