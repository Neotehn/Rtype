# Game Engine

The game engine is the core foundation of any video game: it determines how you represent an object in-game, how the coordinate system works, and how the various systems of your game (graphics, physics, network.. .) communicate.

Our game is built as a [State Machine](../game-engine/state-machine.md) and and each screen is a different state. In order to handle all different entities, like the player, projectiles or enemies we implemented an [Entity Component System](../game-engine/ecs.md). For all different types of events in game, like creating an enemy or detecting a collision, we have implemented many different [systems](../game-engine/systems.md) to each handle it own event.

[Back](../../README.md)
