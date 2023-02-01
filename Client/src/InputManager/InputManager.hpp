/*
** EPITECH PROJECT, 2022
** .
** File description:
** .
*/
#ifndef CLIENT_SRC_INPUTMANAGER_INPUTMANAGER_HPP_
#define CLIENT_SRC_INPUTMANAGER_INPUTMANAGER_HPP_

#include <vector>

#include <SFML/Graphics.hpp>
#include "../../../Game/EventQueue.hpp"

class InputManager {
 public:
  enum Actions {
    START,  // START; OR START;OWN_PLAYER_ID
    UP,     // UP;ID
    DOWN,   // DOWN;ID
    LEFT,   // LEFT;ID
    RIGHT,  // RIGHT;ID
    SHOOT,  // SHOOT;ID;DAMAGE;TYPE
    // DAMAGE = amount of damage based on load time
    // TYPE = 1, 2, ...
    CREATE,  // CREATE;ID;TYPE;TYPE_DATA
    // TYPE = PLAYER, ENEMY, BULLET
    // PLAYER_DATA: X;Y;SPRITE_PATH
    // ENEMY_DATA:  X;Y
    // BULLET_DATA: X;Y
    INCREASE,  // INCREASE;ID;TYPE;VALUE
    // TYPE = LIFE, SPEED, SHOOTING_SPEED
    COLLISION,  // COLLISION;ID1;ID2
    DEAD,       // DEAD;ID
    END,
  };

  InputManager();
  ~InputManager(){};

  void recordInputs(const sf::Event &t_event);
  void popInputs();

  EventQueue getInputs();
  sf::Vector2i getMousePosition();
  bool isMouseLeftClicked();
  bool isMouseRightClicked();

 private:
  std::vector<int> m_input_queue;
};

#endif  // CLIENT_SRC_INPUTMANAGER_INPUTMANAGER_HPP_
