#include "../../Game/Game.hpp"
#include "../../GameEngine/inc/Core.hpp"

int counter;

int action_counter;

int main(int ac, char *av[]) {
  if (std::stoi(av[1]) == 3) {
    Core app = Core();
    app.run();
  } else {
    Game game(std::stoi(av[1]));
    game.run();
  }
  return 0;
}
