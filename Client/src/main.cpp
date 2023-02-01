#include "../../Game/Game.hpp"

int counter;

int action_counter;

int main(int ac, char *av[]) {
  Game game(std::stoi(av[0]));
  game.run();
  return 0;
}
