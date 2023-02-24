# ShootingSystem

This system will detect if you pressed the shooting key (SPACE) and the server will send to the client the command to create a BULLET.

ShootingSystem.hpp:

```
class ShootingSystem : public ISystem {
 public:
  ShootingSystem(std::shared_ptr<EntityManager> t_em, UdpServer *t_serverCom);
  ~ShootingSystem();

  void update();
  void updateData(SystemData &t_data);

 private:
  EventQueue m_event_queue;
  UdpServer *m_serverCom;
};
```

ShootingSystem.cpp:

```
ShootingSystem::ShootingSystem(std::shared_ptr<EntityManager> t_em,
                               UdpServer *t_serverCom) {
  m_em = t_em;
  m_serverCom = t_serverCom;
}

ShootingSystem::~ShootingSystem() {}

void ShootingSystem::updateData(SystemData &t_data) {
  m_event_queue = t_data.event_queue;
}

void ShootingSystem::update() {
  if (m_event_queue.checkIfKeyPressed(Action::ActionType::SHOOT)) {
    for (EntityID ent : EntityViewer<Player>(*m_em.get())) {
      Player *player = (*m_em.get()).Get<Player>(ent);
      EntityID bullet = m_em->createNewEntity();
      SpriteECS sprite = SpriteECS("./../Client/sprites/shoot2.png");
      rtype::Vector2f bullet_pos = {player->position.position.x - 20,
                                    player->position.position.y +
                                      player->body->getSize().y / 2 - 10};
      rtype::IRectangleShape *bullet_body = new rtype::RectangleShape();

      bullet_body->setSize({20, 20});
      bullet_body->setPosition({bullet_pos.x, bullet_pos.y});
      bullet_body->setTexture(sprite.getTexture());

      m_em->Assign<Bullet>(bullet, Bullet{bullet_body, 10.0, bullet_pos});
      m_serverCom->addEvent(std::make_shared<Action>(
        CreateAction(bullet, Action::ObjectType::BULLET, bullet_pos, "")));
    }
  }
}
```

[Back](../game-engine/systems.md)
