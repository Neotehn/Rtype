#include "ShootingSystem.hpp"

ShootingSystem::ShootingSystem(std::shared_ptr<EntityManager> t_em) {
  m_em = t_em;
}

ShootingSystem::~ShootingSystem() {}

void ShootingSystem::updateData(SystemData &t_data) {
  m_event_queue = t_data.event_queue;
}

void ShootingSystem::update() {
  // TODO: handle im Server
  if (m_event_queue.checkIfKeyPressed(Action::ActionType::SHOOT)) {
    for (EntityID ent :
         EntityViewer<float, Pos, sf::RectangleShape>(*m_em.get())) {
      Pos *player = (*m_em.get()).Get<Pos>(ent);
      sf::RectangleShape *body = (*m_em.get()).Get<sf::RectangleShape>(ent);
      EntityID bullet = m_em->createNewEntity();
      SpriteECS sprite = SpriteECS("./../Client/sprites/shoot2.png");
      m_em->Assign<float>(bullet, 10.0);
      sf::Vector2f bullet_pos = {player->position.x - 20,
                                 player->position.y + body->getSize().y / 2 -
                                   10};
      m_em->Assign<sf::Vector2f>(bullet, bullet_pos);

      sf::RectangleShape bullet_body;
      bullet_body.setSize({20, 20});
      bullet_body.setPosition(bullet_pos);
      bullet_body.setTexture(sprite.getTexture());
      m_em->Assign<sf::RectangleShape>(bullet, bullet_body);
    }
  }
}
