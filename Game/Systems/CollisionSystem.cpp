#include "CollisionSystem.hpp"

CollisionSystem::CollisionSystem(std::shared_ptr<EntityManager> t_em) {
  m_em = t_em;
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
      // TODO: do some shit
      //       if (collision) { std::cout << "Collision" << std::endl; }
    }
  }
}
