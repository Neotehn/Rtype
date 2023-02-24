# CollisionSystem

The CollisionSystem checks for collisons with the player and detects if the player got hit or if the player hit an enemy.

CollisionSystem.hpp:

```
class CollisionSystem : public ISystem {
 public:
  CollisionSystem(std::shared_ptr<EntityManager> t_em, UdpServer *t_serverCom);
  ~CollisionSystem();

  void update();
  void updateData(SystemData &t_data);
  void bulletEnemyCollision();

 private:
  std::shared_ptr<EntityManager> m_em;
  UdpServer *m_serverCom;

  EntityID createExplosion();
};
```

CollisionSystem.cpp:

```
CollisionSystem::CollisionSystem(std::shared_ptr<EntityManager> t_em,
                                 UdpServer *t_serverCom) {
  m_em = t_em;
  m_serverCom = t_serverCom;
}

CollisionSystem::~CollisionSystem() {}

void CollisionSystem::updateData(SystemData &t_data) {}

// explosion has no effect on game, therefore, we just need a new entity id
EntityID CollisionSystem::createExplosion() {
  EntityID explosion = m_em->createNewEntity();
  return explosion;
}

void CollisionSystem::update() {
  for (EntityID player_ent : EntityViewer<Player>(*m_em.get())) {
    for (EntityID enemy_ent : EntityViewer<AnimationObj>(*m_em.get())) {
      Player *player = (*m_em.get()).Get<Player>(player_ent);
      AnimationObj *enemy = (*m_em.get()).Get<AnimationObj>(enemy_ent);

      bool collision = player->body->intersects(enemy->body->getGlobalBounds());

      if (collision) {
        if (enemy->type == "enemy") {
          m_serverCom->addEvent(
            std::make_shared<Action>(CollisionAction(player_ent, enemy_ent)));
          m_serverCom->addEvent(std::make_shared<Action>(
            CreateAction(createExplosion(), Action::ObjectType::EXPLOSION,
                         enemy->position.position, "")));
          m_serverCom->addEvent(
            std::make_shared<Action>(DestroyAction(enemy_ent)));
          m_serverCom->addEvent(
            std::make_shared<Action>(DamageAction(enemy_ent, 1)));
          m_em->destroyEntity(enemy_ent);
        } else if (enemy->type == "powerup") {
          m_serverCom->addEvent(std::make_shared<Action>(
            IncreaseAction(player_ent, Action::IncreaseType::LIFE, 1)));
          m_serverCom->addEvent(
            std::make_shared<Action>(DestroyAction(enemy_ent)));
          m_em->destroyEntity(enemy_ent);
        }
      }
    }
  }
  bulletEnemyCollision();
}

void CollisionSystem::bulletEnemyCollision() {
  for (EntityID enemy_ent : EntityViewer<AnimationObj>(*m_em.get())) {
    AnimationObj *enemy = (*m_em.get()).Get<AnimationObj>(enemy_ent);

    if (enemy->type != "enemy") { continue; }
    for (EntityID bullet_ent : EntityViewer<Bullet>(*m_em.get())) {
      Bullet *bullet = (*m_em.get()).Get<Bullet>(bullet_ent);

      bool collision = enemy->body->intersects(bullet->body->getGlobalBounds());
      if (collision) {
        m_serverCom->addEvent(
          std::make_shared<Action>(DestroyAction(enemy_ent)));
        m_serverCom->addEvent(
          std::make_shared<Action>(DestroyAction(bullet_ent)));
        m_em->destroyEntity(enemy_ent);
        m_em->destroyEntity(bullet_ent);
        break;
      }
    }
  }
}
```

[Back](../game-engine/systems.md)
