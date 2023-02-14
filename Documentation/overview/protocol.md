# Protocol

A binary protocol for client/server communications. We must use UDP for communications between the server and the client.

### Commands

Following commands are implemented.

The Transmitted commands are build of multiple arguments. Depending on the action the command contains different arguments. The first argument is an "ACTION\_ID", followed by the command (e.g. "UP", "DOWN", "SHOOT", etc). The third argument is the entity id. Following that the next command is depending on the second argument, you can view that from the following "ActionType" enum.&#x20;

```
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
    // TYPE = PLAYER, ENEMY, BULLET
    // PLAYER_DATA: X;Y;SPRITE_PATH
    // ENEMY_DATA:  X;Y;VELOCITY
    // BULLET_DATA: X;Y
    // EXPLOSION_DATA: X;Y
    // POWER_UP_DATA: X;Y
    INCREASE,  // ACTION_ID;INCREASE;ID;TYPE;VALUE
    // TYPE = LIFE, SPEED, SHOOTING_SPEED
    COLLISION,  // ACTION_ID;COLLISION;ID1;ID2
    DAMAGE,     // ACTION_ID;DAMAGE;ID1;DMG
    DESTROY,    // ACTION_ID;DESTROY;ID1
    DEAD,       // ACTION_ID;DEAD;ID
    END,        // ACTION_ID;END; OR END;PORT_NB
    ERROR,
};
```

[BACK](../)
