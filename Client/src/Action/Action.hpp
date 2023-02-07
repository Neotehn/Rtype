#ifndef R_TYPE_CLIENT_ACTION_HPP
#define R_TYPE_CLIENT_ACTION_HPP

#include <string>

#include "./IAction.hpp"

extern int action_counter;

class Action : public IAction {
 public:
  enum ActionType {
    START,  // START;PORT_NB OR START;OWN_PLAYER_ID
    UP,     // UP;ID;USER_TRIGGERED
    DOWN,   // DOWN;ID;USER_TRIGGERED
    LEFT,   // LEFT;ID;USER_TRIGGERED
    RIGHT,  // RIGHT;ID;USER_TRIGGERED
    POS,    // POS;ID;X;
    SHOOT,  // SHOOT;ID;;USER_TRIGGERED;DAMAGE;TYPE
    // DAMAGE = amount of damage based on load time
    // TYPE = 1, 2, ...
    CREATE,  // CREATE;ID;TYPE;TYPE_DATA
    // TYPE = PLAYER, ENEMY, BULLET
    // PLAYER_DATA: X;Y;SPRITE_PATH
    // ENEMY_DATA:  X;Y;VELOCITY
    // BULLET_DATA: X;Y
    // EXPLOSION_DATA: X;Y
    INCREASE,  // INCREASE;ID;TYPE;VALUE
    // TYPE = LIFE, SPEED, SHOOTING_SPEED
    COLLISION,  // COLLISION;ID1;ID2
    DAMAGE,     // DAMAGE;ID1;DMG
    DESTROY,    // DESTROY;ID1
    DEAD,       // DEAD;ID
    END,        // END; OR END;PORT_NB // TODO
    ERROR,
  };
  enum ObjectType { PLAYER, ENEMY, BULLET, EXPLOSION, ERROR_O };
  enum IncreaseType { SPEED, FIRE_RATE, DAMAGE_I, LIFE, SHIELD, BOMB, ERROR_I };

  Action(ActionType type, EntityID id);
  Action(ActionType type, EntityID id, int t_action_id);
  ~Action();

  std::string getCommand() const override;

  virtual std::string getTypeAsString() const;
  int getActionId() const;
  ActionType getType() const;
  EntityID getId() const override;

  bool isTriggeredByUser() const;
  EntityID getCollisionPartnerId() const;

  ObjectType getCreateType() const;
  sf::Vector2f getCreatePosition() const;
  std::string getCreateSpritePath() const;

  IncreaseType getIncreaseType() const;
  int getIncreaseValue() const;

  int getShootDamage() const;
  int getShootType() const;

  float getVelocity() const;

 protected:
  int m_action_id;
  ActionType m_type;
  EntityID m_id;

  bool m_triggered_by_user = false;
  EntityID m_collision_partner_id = 0;
  ObjectType m_object_type = ObjectType::ERROR_O;
  sf::Vector2f m_position = {0, 0};
  std::string m_sprite_path;
  IncreaseType m_increase_type = IncreaseType::ERROR_I;
  int m_value = 0;
  int m_damage = 0;
  int m_shoot_type = 0;
  float m_velocity = -2;
};

#endif  //R_TYPE_CLIENT_ACTION_HPP
