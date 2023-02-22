#include "ShootingSystem.hpp"

ShootingSystem::ShootingSystem(std::shared_ptr<EntityManager> t_em,
                               UdpServer *t_serverCom,
                               rtype::IGraphicLoader *t_graphic_loader) {
  m_em = t_em;
  m_serverCom = t_serverCom;
  m_graphic_loader = t_graphic_loader;
}

ShootingSystem::~ShootingSystem() {}

void ShootingSystem::updateData(SystemData &t_data) {
  m_event_queue = t_data.event_queue;
}

void ShootingSystem::update() {
  for (std::shared_ptr<Action> action :
       m_event_queue.getAllOfType(Action::ActionType::SHOOT)) {
    switch (action->getShootType()) {
      case Action::ShootingType::NORMAL:
        shoot(action);
        break;
      case Action::ShootingType::FIRE:
        shootFire(action);
        break;
      case Action::ShootingType::BOMB:
        shootBomb(action);
        break;
      default:
        break;
    }
  }
}

void ShootingSystem::shoot(std::shared_ptr<Action> action) {
  Player *player = (*m_em.get()).Get<Player>(action->getId());
  EntityID bullet = m_em->createNewEntity();
  SpriteECS sprite =
    SpriteECS("./../Client/sprites/shoot2.png", m_graphic_loader);
  rtype::Vector2f bullet_pos = {player->position.position.x - 20,
                                player->position.position.y +
                                  player->body->getSize().y / 2 - 10};
  rtype::IRectangleShape *bullet_body = m_graphic_loader->loadRectangleShape();

  bullet_body->setSize({20, 20});
  bullet_body->setPosition({bullet_pos.x, bullet_pos.y});
  bullet_body->setTexture(sprite.getTexture());

  m_em->Assign<Bullet>(bullet, Bullet{bullet_body, 10.0, bullet_pos});
  m_serverCom->addEvent(std::make_shared<Action>(
    CreateAction(bullet, Action::ObjectType::BULLET, bullet_pos,
                 std::to_string(Action::ShootingType::NORMAL))));
}

void ShootingSystem::shootFire(std::shared_ptr<Action> action) {
  Player *player = (*m_em.get()).Get<Player>(action->getId());

  if (player->fire_shot == 0) return;
  player->fire_shot -= 1;
  if (player->fire_shot < 0) player->fire_shot = 0;

  // TODO: replace by actual fire shoot
  EntityID bullet = m_em->createNewEntity();
  SpriteECS sprite =
    SpriteECS("./../Client/sprites/shoot3.png", m_graphic_loader);
  rtype::Vector2f bullet_pos = {player->position.position.x - 20,
                                player->position.position.y +
                                  player->body->getSize().y / 2 - 10};
  rtype::IRectangleShape *bullet_body = m_graphic_loader->loadRectangleShape();

  bullet_body->setSize({20, 20});
  bullet_body->setPosition({bullet_pos.x, bullet_pos.y});
  bullet_body->setTexture(sprite.getTexture());

  m_em->Assign<Bullet>(bullet, Bullet{bullet_body, 10.0, bullet_pos});
  m_serverCom->addEvent(std::make_shared<Action>(
    CreateAction(bullet, Action::ObjectType::BULLET, bullet_pos,
                 std::to_string(Action::ShootingType::FIRE))));
}

void ShootingSystem::shootBomb(std::shared_ptr<Action> action) {
  Player *player = (*m_em.get()).Get<Player>(action->getId());

  if (player->bomb_shot == 0) return;
  player->bomb_shot -= 1;
  if (player->bomb_shot < 0) player->bomb_shot = 0;

  // TODO: replace by actual bomb shoot
  EntityID bullet = m_em->createNewEntity();
  SpriteECS sprite =
    SpriteECS("./../Client/sprites/shoot4.png", m_graphic_loader);
  rtype::Vector2f bullet_pos = {player->position.position.x - 20,
                                player->position.position.y +
                                  player->body->getSize().y / 2 - 10};
  rtype::IRectangleShape *bullet_body = m_graphic_loader->loadRectangleShape();

  bullet_body->setSize({20, 20});
  bullet_body->setPosition({bullet_pos.x, bullet_pos.y});
  bullet_body->setTexture(sprite.getTexture());

  m_em->Assign<Bullet>(bullet, Bullet{bullet_body, 10.0, bullet_pos});
  m_serverCom->addEvent(std::make_shared<Action>(
    CreateAction(bullet, Action::ObjectType::BULLET, bullet_pos,
                 std::to_string(Action::ShootingType::BOMB))));
}
