#include "../../Game/Game.hpp"
#include "../../GameEngine/inc/Core.hpp"

int counter;

int action_counter;

int main(int ac, char *av[]) {
  if (std::stoi(av[1]) == 3) {
    Core app = Core();
    app.run();
  } else {
    if (std::stoi(av[1]) == 1) { action_counter = 1000; }
    Game game(std::stoi(av[1]));
    game.run();
  }
  return 0;
}
