# Systems

To display and handle events for our game we implemented different systems, that have each a special function.
Following systems are implemented:

* [AnimationSystem](../systems/animationsystem.md)
* [CollisionSystem](../systems/collisionsystem.md)
* [CreateObjectSystem](../systems/createobjectsystem.md)
* [DamageSystem](../systems/damagesystem.md)
* [DestroySystem](../systems/destroysystem.md)
* [DisplaySystem](../systems/displaysystem.md)
* [MovementSystem](../systems/movementsystem.md)
* [PowerUpSystem](../systems/powerupsystem.md)
* [RandomEnemyGeneratorSystem](../systems/randomenemygeneratorsystem.md)
* [ShootingSystem](../systems/shootingsystem.md)
* [SoundSystem](../systems/soundsystem.md)

The GameState contains a vector that contains all different systems and in the update function of the GameState the systems get updated and excecuted.