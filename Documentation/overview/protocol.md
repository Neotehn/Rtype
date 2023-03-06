# Protocol

A protocol for client/server communications. We must use UDP for communications between the server and the client.

### Architecture

R-Type is build like a classic server-client game. The game runs in the server and the client has to connect to the server. The connection works through an UDP protocol.

### Commands

The transmitted payload follows a simple structure: ACTION\_ID;ACTION\_TYPE;ID;DATA;.

Where ACTION\_ID is an integer that grows with every new action. ACTION\_TYPE is the transmitted action we want to convey (see implemented commands below). The ID is the user id and DATA depends on the ACTION\_TYPE (see implemented commands below).

Following commands are implemented:

```
enum ActionType {
    START,    // ACTION_ID;START;PORT_NB OR START;OWN_PLAYER_ID
    RESTART,  // ACTION_ID;RESTART;LEVEL
    UP,       // ACTION_ID;UP;ID;USER_TRIGGERED
    DOWN,     // ACTION_ID;DOWN;ID;USER_TRIGGERED
    LEFT,     // ACTION_ID;LEFT;ID;USER_TRIGGERED
    RIGHT,    // ACTION_ID;RIGHT;ID;USER_TRIGGERED
    POS,      // ACTION_ID;POS;ID;X;
    SHOOT,    // ACTION_ID;SHOOT;ID;;USER_TRIGGERED;DAMAGE;TYPE
    // DAMAGE = amount of damage based on load time
    // TYPE = 1, 2, ...
    CREATE,  // ACTION_ID;CREATE;ID;TYPE;TYPE_DATA
    // TYPE = PLAYER, ENEMY, BULLET, EXPLOSION, POWER_UP, ITEM
    // PLAYER_DATA: X;Y;SPRITE_PATH
    // ENEMY_DATA:  X;Y;VELOCITY
    // BULLET_DATA: X;Y;SHOOTING_TYPE;OWNER_ID
    // EXPLOSION_DATA: X;Y
    // POWER_UP_DATA: X;Y
    // ITEM:  X;Y;ITEM_TYPE
    INCREASE,  // ACTION_ID;INCREASE;ID;TYPE;VALUE
    // TYPE = LIFE, SPEED, SHOOTING_SPEED
    COLLISION,          // ACTION_ID;COLLISION;ID1;ID2
    DAMAGE,             // ACTION_ID;DAMAGE;ID1;DMG
    DESTROY,            // ACTION_ID;DESTROY;ID1
    DEAD,               // ACTION_ID;DEAD;ID
    END,                // ACTION_ID;END; OR END;PORT_NB
    JOINLOBBY,          // ACTION_ID;LOBBY_IP;LOBBY_ID;PLAYERNAME
    CREATELOBBY,        // ACTION_ID;LOBBY_IP;PLAYERNAME
    LEAVELOBBY,         // ACTION_ID;LOBBY_IP;PLAYERNAME
    JOINSUCCESSFULL,    // ACTION_ID;
    CREATESUCCESSFULL,  // ACTION_ID;
    ERROR,
  };
```

The exact structure of the commands are explained throughout the document. All commands are written in one line and separated by a semicolon(;) and end with a semicolon(;).

### Server connection

When the server is running it waits for a client to connect. The client has two options: create a lobby or join a lobby.

In case the client chooses to create a lobby the client must send following command:

```
ACTION_ID = automatic generated value
ACTION_TYPE = CREATELOBBY
ACTION_TYPE_ID = 16
LOBBY_IP = generated lobby code
PLAYERNAME = username
```

Now the server waits for a second connection. When a second player wants to join a lobby the client must send following command:

```
ACTION_ID = automatic generated value
ACTION_TYPE = JOINLOBBY
ACTION_TYPE_ID = 15
LOBBY_IP = lobby ip you want to join
PLAYERNAME = username
```

If the connection is successful the server sends back following command:

```
ACTION_ID = automatic generated value
ACTION_TYPE = JOINSUCCESSFULL
ACTION_TYPE_ID = 18
PLAYERNAME1 = username of player one
PLAYERNAME2 = username of player two
```

The client also has the option to leave the current lobby. For that the client sends the LEAVELOBBY command:

```
ACTION_ID = automatic generated value
ACTION_TYPE = LEAVELOBBY
ACTION_TYPE_ID = 17
LOBBY_IP = lobby ip of current lobby
PLAYERNAME = username
```

In response the server sends the same command to both clients, in order to confirm the action and to let the other player know the client has left his lobby.

Once both player are connected the players can press the start button and have to send the start command:

```
ACTION_ID = automatic generated value
ACTION_TYPE = START;
PORT_NB = your port;
CURRENT_PLAYER_ID = 0
```

The server registers the port and as soon as both clients are connected the server sends a START command back:

```
ACTION_ID = automatic generated value
ACTION_TYPE = START;
PLAYER_ID = id of player
PLAYER_NB = 1 or 2 depending on which player
```

After that the client must receive the CREATE command for the both player character:

```
ACTION_ID = automatic generated value
ACTION_TYPE = CREATE;
PLAYER_ID = id of player
OBJECT_TYP = 0 for PLAYER
X_POS = x coordinate for spawn
Y_POS = y coordinate for spawn
SPRITE_PATH = path to player sprite
PLAYER_NB = 1 or 2 depending on which player
```

Now the game will start. The client and server now send each other new commands if there is a new action.

### Game

Once the game is running the client sends the player input or an end command to the server. The following ACTION\_TYPES are possible:

```
enum ActionType {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SHOOT,
    END,
};
```

For the player movement the command has the same structure:

```
ACTION_ID = automatic generated value 
ACTION_TYPE = UP / DOWN / LEFT / RIGHT
ID = id of the player
USER_TRIGGERED = TRUE (bool)
```

The server answers with the new position of the player:

```
ACTION_ID = automatic generated value
ACTION_TYPE = POS
ID = id of the player
X = new x coordinate of the player
Y = new y coordinate of the player 
```

The SHOOT command follows following structure:

```
ACTION_ID = automatic generated value
ACTION_TYPE = SHOOT
ID = id of the player
USER_TRIGGERED = TRUE (bool)
DAMAGE = amount of damage based on load time
TYPE = 1, 2, ... (what kind of bullet gets shot)
```

The server answers with a CREATE command for the bullet:

```
ACTION_ID = automatic generated value
ACTION_TYPE = CREATE
ID = id of the the bullet
TYPE = BULLET (2)
X = x coordinate of bullet
Y = y coordinate of bullet
```

If the client window gets closed the client sends a command that disconnects the server and the client:

```
ACTION_ID = automatic generated value
ACTION_TYPE = END
PORT_NB = port the client is running in
```



[Back](../../README.md)
