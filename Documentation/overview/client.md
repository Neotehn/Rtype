# Client

The client is the display terminal of the game. It must display the game and handle input.

The Client works as a state machine and every screen is in a different state. To add new screens please refer to the "[State Machine](../game-engine/state-machine.md)" page.&#x20;

In order to communicate with the server we use our "UDPClient" protocol. For better understanding in how the protocol works please refer to  the "[Protocol](protocol.md)" page.

To be concise the client just transmits the user input (movement, shooting and close game) and everything else, like new enemies or bullets or status updates are all coming from the server.

[Back](../../README.md)
