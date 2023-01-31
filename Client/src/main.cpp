#include "../../Game/ECS/EntityManager.hpp"
#include "../../Game/ECS/ISystem.hpp"
#include "InputManager/InputManager.hpp"&
#include "../../Game/Game.hpp"

int counter;

int main() {
  InputManager input_manager;
  Game game = Game();
  sf::RenderWindow &window = game.getWindow();

  game.run();

//  while (window.isOpen()) {
//    sf::Event event;
//    while (window.pollEvent(event)) {
//      if (event.type == sf::Event::Closed) window.close();
//      input_manager.recordInputs(event);
//    }
//    // TODO: send inputs to the game
//  }

  return 0;
}
