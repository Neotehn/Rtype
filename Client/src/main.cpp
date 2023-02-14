#include "../../Game/Game.hpp"
#include "../../GameEngine/inc/Core.hpp"

int counter;

int action_counter;

int main(int ac, char *av[]) {
  int command = std::stoi(av[1]);

  if (std::stoi(av[1]) == 1) { action_counter = 1000; }

  if (!command) {
    Game game(command);
    game.run();
  } else {
    Game game(command, av[2]);
    game.run();
  }
  return 0;
}
