#include "ShootingSystem.hpp"

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
    for (EntityID ent :
         EntityViewer<float, Pos, sf::RectangleShape>(*m_em.get())) {
      Pos *player = (*m_em.get()).Get<Pos>(ent);
      sf::RectangleShape *body = (*m_em.get()).Get<sf::RectangleShape>(ent);
      EntityID bullet = m_em->createNewEntity();
      SpriteECS sprite = SpriteECS("./../Client/sprites/shoot2.png");
      sf::Vector2f bullet_pos = {player->position.x - 20,
                                 player->position.y + body->getSize().y / 2 -
                                   10};
      sf::RectangleShape bullet_body;

      bullet_body.setSize({20, 20});
      bullet_body.setPosition(bullet_pos);
      bullet_body.setTexture(sprite.getTexture());
      m_em->Assign<Bullet>(bullet, Bullet{10.0, bullet_pos, bullet_body});
      m_serverCom->addEvent(std::make_shared<Action>(
        CreateAction(bullet, Action::ObjectType::BULLET, bullet_pos, "")));
    }
  }
}
