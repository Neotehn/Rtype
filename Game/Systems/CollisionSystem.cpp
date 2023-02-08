#include "CollisionSystem.hpp"
#include <memory>

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
  for (EntityID player_ent :
       EntityViewer<float, Pos, sf::RectangleShape>(*m_em.get())) {
    for (EntityID enemy_ent :
         EntityViewer<std::string, Pos, sf::RectangleShape>(*m_em.get())) {
      sf::RectangleShape *player_body =
        (*m_em.get()).Get<sf::RectangleShape>(player_ent);
      Pos *enemy_pos = (*m_em.get()).Get<Pos>(enemy_ent);
      std::string *enemy_type = (*m_em.get()).Get<std::string>(enemy_ent);
      sf::RectangleShape *enemy_body =
        (*m_em.get()).Get<sf::RectangleShape>(enemy_ent);
      bool collision = player_body->getGlobalBounds().intersects(
        enemy_body->getGlobalBounds());

      if (collision) {
        if (*enemy_type == "enemy") {
          m_serverCom->addEvent(
            std::make_shared<Action>(CollisionAction(player_ent, enemy_ent)));
          m_serverCom->addEvent(std::make_shared<Action>(
            CreateAction(createExplosion(), Action::ObjectType::EXPLOSION,
                         enemy_pos->position, "")));
          m_serverCom->addEvent(
            std::make_shared<Action>(DestroyAction(enemy_ent)));
          m_serverCom->addEvent(
            std::make_shared<Action>(DamageAction(enemy_ent, 1)));
          m_em->destroyEntity(enemy_ent);
        }
        if (*enemy_type == "powerup") {
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
  for (EntityID enemy_ent :
       EntityViewer<std::string, Pos, sf::RectangleShape>(*m_em.get())) {
    std::string *enemy_type = (*m_em.get()).Get<std::string>(enemy_ent);

    if (*enemy_type != "enemy") { continue; }
    for (EntityID bullet_ent : EntityViewer<Bullet>(*m_em.get())) {
      sf::RectangleShape *enemy_body =
        (*m_em.get()).Get<sf::RectangleShape>(enemy_ent);
      Bullet *bullet = (*m_em.get()).Get<Bullet>(bullet_ent);

      bool collision = enemy_body->getGlobalBounds().intersects(
        bullet->bullet_body.getGlobalBounds());
      if (collision) {
        m_serverCom->addEvent(
          std::make_shared<Action>(DestroyAction(enemy_ent)));
        m_serverCom->addEvent(
          std::make_shared<Action>(DestroyAction(bullet_ent)));
        m_em->destroyEntity(enemy_ent);
        m_em->destroyEntity(bullet_ent);
      }
    }
  }
}