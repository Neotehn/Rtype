#include "../../Game/Game.hpp"
#include "../../GameEngine/inc/Core.hpp"
#include "../../Game/Encapsulation/Networking/Boost/IoService.hpp"

int counter;

int action_counter;

int main(int ac, char *av[]) {
  if (std::stoi(av[1]) == 1) { action_counter = 1000; }
  rtype::IoService io_service;
  Game game(std::stoi(av[1]), io_service);
  game.run();
  return 0;
}
