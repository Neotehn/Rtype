#ifndef R_TYPE_CLIENT_ACTION_HPP
#define R_TYPE_CLIENT_ACTION_HPP

#include <string>

#include "./IAction.hpp"
#include "../../../Game/Encapsulation/GraphicDataTypes.hpp"

extern int action_counter;

class Action : public IAction {
 public:
  enum ActionType {
    START,  // ACTION_ID;START;PORT_NB OR START;OWN_PLAYER_ID
    UP,     // ACTION_ID;UP;ID;USER_TRIGGERED
    DOWN,   // ACTION_ID;DOWN;ID;USER_TRIGGERED
    LEFT,   // ACTION_ID;LEFT;ID;USER_TRIGGERED
    RIGHT,  // ACTION_ID;RIGHT;ID;USER_TRIGGERED
    POS,    // ACTION_ID;POS;ID;X;
    SHOOT,  // ACTION_ID;SHOOT;ID;;USER_TRIGGERED;DAMAGE;TYPE
    // DAMAGE = amount of damage based on load time
    // TYPE = 1, 2, ...
    CREATE,  // ACTION_ID;CREATE;ID;TYPE;TYPE_DATA
    // TYPE = PLAYER, ENEMY, BULLET, EXPLOSION, POWER_UP, ITEM
    // PLAYER_DATA: X;Y;SPRITE_PATH
    // ENEMY_DATA:  X;Y;VELOCITY
    // BULLET_DATA: X;Y;SHOOTING_TYPE
    // EXPLOSION_DATA: X;Y
    // POWER_UP_DATA: X;Y
    // ITEM:  X;Y;ITEM_TYPE
    INCREASE,  // ACTION_ID;INCREASE;ID;TYPE;VALUE
    // TYPE = LIFE, SPEED, SHOOTING_SPEED
    COLLISION,  // ACTION_ID;COLLISION;ID1;ID2
    DAMAGE,     // ACTION_ID;DAMAGE;ID1;DMG
    DESTROY,    // ACTION_ID;DESTROY;ID1
    DEAD,       // ACTION_ID;DEAD;ID
    END,        // ACTION_ID;END; OR END;PORT_NB
    ERROR,
  };
  enum ShootingType { NORMAL, FIRE, BOMB };
  enum ObjectType { PLAYER, ENEMY, BULLET, EXPLOSION, POWER_UP, ITEM, ERROR_O };
  enum IncreaseType {
    SPEED,
    FIRE_SHOT,
    DAMAGE_I,
    LIFE,
    SHIELD,
    BOMB_SHOT,
    COINS,
    ERROR_I
  };

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
  rtype::Vector2f getCreatePosition() const;
  std::string getCreateSpritePath() const;

  IncreaseType getIncreaseType() const;
  int getIncreaseValue() const;

  int getShootDamage() const;
  ShootingType getShootType() const;

  float getVelocity() const;
  int getItemType() const;

  void setPlayerId(EntityID t_id);

 protected:
  int m_action_id;
  ActionType m_type;
  EntityID m_id;

  bool m_triggered_by_user = false;
  EntityID m_collision_partner_id = 0;
  ObjectType m_object_type = ObjectType::ERROR_O;
  rtype::Vector2f m_position = {0, 0};
  std::string m_sprite_path;
  IncreaseType m_increase_type = IncreaseType::ERROR_I;
  int m_value = 0;
  int m_damage = 0;
  ShootingType m_shoot_type = ShootingType::NORMAL;
  float m_velocity = -2;
  int m_item_type = 0;
};

#endif  //R_TYPE_CLIENT_ACTION_HPP
