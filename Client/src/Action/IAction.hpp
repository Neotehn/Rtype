#ifndef R_TYPE_CLIENT_IACTION_HPP
#define R_TYPE_CLIENT_IACTION_HPP

#include <string>

#include "../../../Game/ECS/ECS.hpp"

extern int action_counter;

class IAction {
 public:
  enum ActionType {
    START,  // START;PORT_NB OR START;OWN_PLAYER_ID
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
    END,        // END; OR END;PORT_NB // TODO
  };

  IAction(ActionType type, EntityID id) : m_type(type), m_id(id) {
    m_action_id = action_counter++;
  }
  IAction(ActionType type, EntityID id, int t_action_id)
      : m_type(type), m_id(id) {
    m_action_id = t_action_id;
  }
  virtual ~IAction() = default;

  virtual std::string getCommand() const { return ""; };

  virtual ActionType getType() const { return m_type; }
  virtual EntityID getId() const { return m_id; }

 protected:
  int m_action_id;
  ActionType m_type;
  EntityID m_id;
};

#endif  //R_TYPE_CLIENT_IACTION_HPP
