# Protocol

A binary protocol for client/server communications. We must use UDP for communications between the server and the client.

### Architecture

The architecture is a client-server game architecture. The game is handled in the server. The client connects to the server by using an UDP protocol.

### Commands

The transmitted payload follows a simple structure: ACTION\_ID;ACTION\_TYPE;ID;DATA;.

Where ACTION\_ID is an integer that grows with every new action. ACTION\_TYPE is the transmitted action we want to convey (see implemented commands below). The ID is the user id and DATA depends on the ACTION\_TYPE (see implemented commands below).

Following commands are implemented:

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

### Server connection

The server waits till a clients starts to connect with it. To connect with the server the client needs to send following command to the server: 1000;START;PORT\_NB;.

On success the server answers with the command to create the player (0;CREATE;ID;PLAYER;X\_CORD;Y\_CORD;SPRITE\_PATH;.

### Game

The client transmits player events. These are defined in the ActionType enumeration. To clarify which events are player events, you will find a slimmed down version below.

```
enum ActionType {
    UP,
    DOWN,
    RIGHT,
    LEFT,
    SHOOT,
};
```

The server responds to these actions by sending the new position of the player. In case of the SHOOT action, the server sends the CREATE action to create a new bullet at the required position.

[Back](../../README.md)
