#include "CollisionSystem.hpp"
#include <memory>

CollisionSystem::CollisionSystem(std::shared_ptr<EntityManager> t_em,
                                 UdpServer *t_serverCom,
                                 rtype::IGraphicLoader *t_graphic_loader) {
  m_em = t_em;
  m_serverCom = t_serverCom;
  m_graphic_loader = t_graphic_loader;
}

void CollisionSystem::updateData(SystemData &t_data) {}

// explosion has no effect on game, therefore, we just need a new entity id
EntityID CollisionSystem::createExplosion() {
  EntityID explosion = m_em->createNewEntity();
  return explosion;
}

void CollisionSystem::update() {
  for (EntityID player_ent : EntityViewer<Player>(*m_em)) {
    Player *player = (*m_em).Get<Player>(player_ent);
    //    if (player->health.healthbar.getHealth() > 0) {
    playerAnimationCollision(player, player_ent);
    playerItemCollision(player, player_ent);
    //    }
  }
  bulletEnemyCollision();
}

void CollisionSystem::playerAnimationCollision(Player *t_player,
                                               EntityID t_player_ent) {
  for (EntityID enemy_ent : EntityViewer<AnimationObj>(*m_em)) {
    AnimationObj *enemy = (*m_em).Get<AnimationObj>(enemy_ent);

    bool collision = t_player->body->intersects(enemy->body->getGlobalBounds());

    if (collision) {
      if (enemy->type == "powerup") {
        t_player->coins += 1;
        t_player->coin_shot += 10;
        m_serverCom->addEvent(std::make_shared<Action>(
          IncreaseAction(t_player_ent, Action::IncreaseType::COINS, 10)));
        m_serverCom->addEvent(
          std::make_shared<Action>(DestroyAction(enemy_ent)));
        m_em->destroyEntity(enemy_ent);
      }
    }
  }

  for (EntityID enemy_ent : EntityViewer<Enemy>(*m_em)) {
    Enemy *enemy = (*m_em).Get<Enemy>(enemy_ent);
    bool collision =
      t_player->body->intersects(enemy->obj->body->getGlobalBounds());

    if (collision) {
      t_player->health.healthbar.decreaseHealth(1);
      if (t_player->health.healthbar.getHealth() == 0) {
        t_player->fire_shot = 0;
        t_player->coin_shot = 0;
        t_player->bomb_shot = 0;
        t_player->exp = 0;
      }
      if (enemy->obj->type == "paywall" || enemy->obj->type == "endboss") {
        m_serverCom->addEvent(
          std::make_shared<Action>(DamageAction(enemy_ent, 1, t_player_ent)));
      } else if (enemy->obj->type == "enemy") {
        m_serverCom->addEvent(
          std::make_shared<Action>(CollisionAction(t_player_ent, enemy_ent)));
        m_serverCom->addEvent(std::make_shared<Action>(
          CreateAction(createExplosion(), Action::ObjectType::EXPLOSION,
                       enemy->obj->position.position, "")));
        m_serverCom->addEvent(
          std::make_shared<Action>(DestroyAction(enemy_ent)));
        m_serverCom->addEvent(
          std::make_shared<Action>(DamageAction(enemy_ent, 1, t_player_ent)));
        m_em->destroyEntity(enemy_ent);
      }
    }
  }
}

void CollisionSystem::playerItemCollision(Player *t_player,
                                          EntityID t_player_ent) {
  for (EntityID item_ent : EntityViewer<SpinningItem>(*m_em)) {
    SpinningItem *item = (*m_em).Get<SpinningItem>(item_ent);

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

void CollisionSystem::protectionBulletStream(Enemy *t_enemy, int t_damage) {
  for (int nb = 0; nb < t_enemy->health.max_health; nb += 100) {
    if (t_enemy->health.cur_health > nb &&
        t_enemy->health.cur_health - t_damage <= nb) {
      for (float i = (700 - nb); i <= (100 + nb); i += 200) {
        initEnemy(m_em, m_graphic_loader, m_serverCom,
                  {t_enemy->obj->position.position.x, i}, 1);
      }
    }
  }
}

void CollisionSystem::bulletEnemyCollision() {
  for (EntityID enemy_ent : EntityViewer<Enemy>(*m_em)) {
    Enemy *enemy = (*m_em).Get<Enemy>(enemy_ent);

    for (EntityID bullet_ent : EntityViewer<Bullet>(*m_em)) {
      Bullet *bullet = (*m_em).Get<Bullet>(bullet_ent);

      bool collision =
        enemy->obj->body->intersects(bullet->body->getGlobalBounds());
      if (collision) {
        if (enemy->obj->type == "paywall" && bullet->damage < 6) continue;
        if (enemy->obj->type == "paywall") {
          bullet->damage = 2;
          protectionBulletStream(enemy, bullet->damage);
        }
        enemy->health.cur_health -= bullet->damage;
        if (enemy->health.cur_health <= 0) {
          enemy->health.cur_health = 0;
          m_serverCom->addEvent(std::make_shared<Action>(
            IncreaseAction(bullet->owner, Action::IncreaseType::KILLS,
                           enemy->obj->kill_value)));
          m_serverCom->addEvent(
            std::make_shared<Action>(DestroyAction(enemy_ent)));
          m_serverCom->addEvent(
            std::make_shared<Action>(DestroyAction(bullet_ent)));
          m_em->destroyEntity(enemy_ent);
        } else {
          m_serverCom->addEvent(std::make_shared<Action>(
            IncreaseAction(bullet->owner, Action::IncreaseType::KILLS,
                           enemy->obj->kill_value)));
          m_serverCom->addEvent(std::make_shared<Action>(
            DamageAction(enemy_ent, bullet->damage, enemy_ent)));
          m_serverCom->addEvent(
            std::make_shared<Action>(DestroyAction(bullet_ent)));
        }
        m_em->destroyEntity(bullet_ent);
        break;
      }
    }
  }
}