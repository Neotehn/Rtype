#ifndef R_TYPE_CLIENT_ACTION_HPP
#define R_TYPE_CLIENT_ACTION_HPP

#include <string>

#include "./IAction.hpp"

extern int action_counter;

class Action : public IAction {
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
    ERROR,
  };
  enum ObjectType { PLAYER, ENEMY, BULLET, ERROR_O };
  enum IncreaseType { SPEED, FIRE_RATE, DAMAGE, LIFE, SHIELD, BOMB, ERROR_I };

  Action(ActionType type, EntityID id);
  Action(ActionType type, EntityID id, int t_action_id);
  ~Action();

  std::string getCommand() const override;

  virtual std::string getTypeAsString() const;
  int getActionId() const;
  ActionType getType() const;
  EntityID getId() const override;

  EntityID getCollisionPartnerId() const;

  ObjectType getCreateType() const;
  sf::Vector2f getCreatePosition() const;
  std::string getCreateSpritePath() const;

  IncreaseType getIncreaseType() const;
  int getIncreaseValue() const;

  int getShootDamage() const;
  int getShootType() const;

 protected:
  int m_action_id;
  ActionType m_type;
  EntityID m_id;

  EntityID m_collision_partner_id;
  ObjectType m_object_type = ObjectType::ERROR_O;
  sf::Vector2f m_position = {0, 0};
  std::string m_sprite_path;
  IncreaseType m_increase_type = IncreaseType::ERROR_I;
  int m_value;
  int m_damage;
  int m_shoot_type;
};

#endif  //R_TYPE_CLIENT_ACTION_HPP
