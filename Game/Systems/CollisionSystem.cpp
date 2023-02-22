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
  for (EntityID player_ent : EntityViewer<Player>(*m_em.get())) {
    Player *player = (*m_em.get()).Get<Player>(player_ent);
    playerAnimationCollision(player, player_ent);
    playerItemCollision(player, player_ent);
  }
  bulletEnemyCollision();
}

void CollisionSystem::playerAnimationCollision(Player *t_player,
                                               EntityID t_player_ent) {
  for (EntityID enemy_ent : EntityViewer<AnimationObj>(*m_em.get())) {
    AnimationObj *enemy = (*m_em.get()).Get<AnimationObj>(enemy_ent);

    bool collision = t_player->body->intersects(enemy->body->getGlobalBounds());

    if (collision) {
      if (enemy->type == "enemy") {
        m_serverCom->addEvent(
          std::make_shared<Action>(CollisionAction(t_player_ent, enemy_ent)));
        m_serverCom->addEvent(std::make_shared<Action>(
          CreateAction(createExplosion(), Action::ObjectType::EXPLOSION,
                       enemy->position.position, "")));
        m_serverCom->addEvent(
          std::make_shared<Action>(DestroyAction(enemy_ent)));
        m_serverCom->addEvent(
          std::make_shared<Action>(DamageAction(enemy_ent, 1)));
        m_em->destroyEntity(enemy_ent);
      } else if (enemy->type == "powerup") {
        t_player->coins += 1;
        m_serverCom->addEvent(std::make_shared<Action>(
          IncreaseAction(t_player_ent, Action::IncreaseType::COINS, 1)));
        m_serverCom->addEvent(
          std::make_shared<Action>(DestroyAction(enemy_ent)));
        m_em->destroyEntity(enemy_ent);
      }
    }
  }
}

void CollisionSystem::playerItemCollision(Player *t_player,
                                          EntityID t_player_ent) {
  for (EntityID item_ent : EntityViewer<SpinningItem>(*m_em.get())) {
    SpinningItem *item = (*m_em.get()).Get<SpinningItem>(item_ent);

    bool collision = t_player->body->intersects(item->body->getGlobalBounds());

    if (collision) {
      Action::IncreaseType item_increase = Action::IncreaseType::ERROR_I;
      int value = 0;

      switch (item->type) {
        case rtype::ItemType::LIFE_ITEM:
          item_increase = Action::IncreaseType::LIFE;
          value = 1;
          t_player->health.healthbar.increaseHealth(value);
          break;
        case rtype::ItemType::FIRE_ITEM:
          item_increase = Action::IncreaseType::FIRE_SHOT;
          value = 5;
          t_player->fire_shot += value;
          break;
        case rtype::ItemType::BOMB_ITEM:
          item_increase = Action::IncreaseType::BOMB_SHOT;
          value = 5;
          t_player->bomb_shot += value;
          break;
        case rtype::ItemType::SPEED_ITEM:
          item_increase = Action::IncreaseType::SPEED;
          value = 3;
          t_player->speed += value;
          break;
        default:
          break;
      }

      m_serverCom->addEvent(std::make_shared<Action>(DestroyAction(item_ent)));
      m_serverCom->addEvent(std::make_shared<Action>(
        IncreaseAction(t_player_ent, item_increase, value)));
      m_em->destroyEntity(item_ent);
    }
  }
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