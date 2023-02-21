#include "../../GameEngine/src/Core.hpp"

int counter;

int action_counter;

int main(int ac, char *av[]) {
  int command = std::stoi(av[1]);

  if (std::stoi(av[1]) == 1) {
    if (ac != 3) {
      std::cout << "No Ip given" << std::endl;
      return 84;
    }
    action_counter = 1000;
    Core core(std::stoi(av[1]), av[2]);
    core.run();
  } else {
    Core core(std::stoi(av[1]));
    core.run();
  }
  return 0;
}
