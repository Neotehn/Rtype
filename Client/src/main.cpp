#include <thread>

#include "../../Game/ECS/EntityManager.hpp"
#include "../../Game/ECS/ISystem.hpp"
#include "InputManager/InputManager.hpp"
#include "../../Game/Game.hpp"

int counter;

void runGame(Game *t_game) { t_game->run(); }

void recordInputs(Game *t_game) {
  sf::RenderWindow &window = t_game->getWindow();
  InputManager &input_manager = t_game->getInputManager();

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
      input_manager.recordInputs(event);
    }
  }
}

int main() {
  Game game = Game();

  std::thread game_thread(runGame, &game);
  // TODO: set locks for input manager and window (in game?)
  std::thread input_thread(recordInputs, &game);

  game_thread.join();
  input_thread.join();
  return 0;
}
