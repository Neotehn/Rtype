#include "../../GameEngine/src/Core.hpp"

int counter;

int action_counter;

int main(int ac, char *av[]) {
  if (std::stoi(av[1]) == 1) { action_counter = 1000; }
  Core core(std::stoi(av[1]), av[2]);
  core.run();
  return 0;
}
