#include "CollisionSystem.hpp"
#include <memory>

CollisionSystem::CollisionSystem(std::shared_ptr<EntityManager> t_em,
                                 UdpServer *t_serverCom) {
  m_em = t_em;
  m_serverCom = t_serverCom;
}

CollisionSystem::~CollisionSystem() {}

void CollisionSystem::updateData(SystemData &t_data) {}

void CollisionSystem::update() {
  for (EntityID player_ent :
       EntityViewer<float, Pos, sf::RectangleShape>(*m_em.get())) {
    for (EntityID enemy_ent :
         EntityViewer<std::string, Pos, sf::RectangleShape>(*m_em.get())) {
      sf::RectangleShape *player_body =
        (*m_em.get()).Get<sf::RectangleShape>(player_ent);
      sf::RectangleShape *enemy_body =
        (*m_em.get()).Get<sf::RectangleShape>(enemy_ent);
      bool collision = player_body->getGlobalBounds().intersects(
        enemy_body->getGlobalBounds());

      if (collision) {
        m_serverCom->addEvent(
          std::make_shared<Action>(CollisionAction(player_ent, enemy_ent)));
        m_serverCom->addEvent(
          std::make_shared<Action>(DestroyAction(enemy_ent)));
        m_em->destroyEntity(enemy_ent);
      }
    }
  }
}
