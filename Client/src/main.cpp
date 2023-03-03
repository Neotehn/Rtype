#include "../../GameEngine/src/Core.hpp"

int counter;

int action_counter;

int main(int ac, char *av[]) {
  if (std::stoi(av[1]) == 1) { action_counter = 10000; }
  int *level = new int(1);
  Core core(std::stoi(av[1]), av[2], level);
  core.run();
  return 0;
}
