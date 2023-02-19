/*
** EPITECH PROJECT, 2022
** .
** File description:
** .
*/
#include "MovementSystem.hpp"

void keepPlayerInsideScreen(rtype::Vector2f &t_position,
                            const rtype::Vector2f &t_size) {
  int screen_width = 800;
  int screen_height = 800;
  if (t_position.x - t_size.x <= 0) {
    t_position.x = t_size.x;
  } else if (t_position.x >= screen_width) {
    t_position.x = screen_width;
  }
  if (t_position.y < 0) {
    t_position.y = 0;
  } else if (t_position.y + t_size.y >= screen_height) {
    t_position.y = screen_height - t_size.y;
  }
}

MovementSystem::MovementSystem(std::shared_ptr<EntityManager> t_em,
                               UdpServer *t_serverCom) {
  m_em = t_em;
  m_serverCom = t_serverCom;
}

MovementSystem::~MovementSystem() {}

void MovementSystem::updateData(SystemData &t_data) {
  m_event_queue = t_data.event_queue;
}

void MovementSystem::update() {
  for (EntityID ent : EntityViewer<Player>(*m_em.get())) {
    updatePlayer(ent);
  }
  for (EntityID ent : EntityViewer<BackgroundLayer>(*m_em.get())) {
    updateBackground(ent);
  }
  for (EntityID ent : EntityViewer<Bullet>(*m_em.get())) {
    updateBullets(ent);
  }
  for (EntityID ent : EntityViewer<AnimationObj>(*m_em.get())) {
    AnimationObj *anim = (*m_em.get()).Get<AnimationObj>(ent);
    anim->position.position += anim->position.velocity;
    anim->body->setPosition(
      {anim->position.position.x, anim->position.position.y});
  }
}

void MovementSystem::updatePlayer(EntityID t_ent) {
  Player *player = (*m_em.get()).Get<Player>(t_ent);
  rtype::Vector2f direction = {0, 0};
  if (m_event_queue.checkIfKeyPressed(Action::ActionType::LEFT)) {
    direction.x = -1;
  }
  if (m_event_queue.checkIfKeyPressed(Action::ActionType::RIGHT)) {
    direction.x = 1;
  }
  if (m_event_queue.checkIfKeyPressed(Action::ActionType::UP)) {
    direction.y = -1;
  }
  if (m_event_queue.checkIfKeyPressed(Action::ActionType::DOWN)) {
    direction.y = 1;
  }
  if (direction.x != 0 || direction.y != 0) {
    player->position.velocity = direction * player->speed;
  }
  player->position.position += player->position.velocity;
  keepPlayerInsideScreen(
    player->position.position,
    {player->body->getSize().x, player->body->getSize().y});
  if (m_event_queue.checkIfKeyPressed(Action::ActionType::POS)) {
    player->position.position = m_event_queue.getLatestPos(t_ent);
  }
  player->body->setPosition(
    {player->position.position.x, player->position.position.y});
  player->health.body->setPosition(
    {player->position.position.x - 180, player->position.position.y - 70});

  if (player->position.velocity.x != 0 || player->position.velocity.y != 0)
    player->position.velocity *= 0.99f;
  if (m_serverCom != nullptr && direction != rtype::Vector2f{0, 0}) {
    m_serverCom->addEvent(
      std::make_shared<Action>(PosAction(t_ent, player->position.position)));
  }
}

void MovementSystem::updateBackground(EntityID t_ent) {
  BackgroundLayer *layer = (*m_em.get()).Get<BackgroundLayer>(t_ent);
  layer->position.x -= layer->speed;
  if (layer->position.x <= layer->limit) { layer->position.x = 0; }
  layer->sprite.setPosition(layer->position);
}

void MovementSystem::updateBullets(EntityID t_ent) {
  Bullet *bullet = (*m_em.get()).Get<Bullet>(t_ent);

  bullet->pos.x += bullet->speed;
  if (bullet->pos.x >= 800) { m_em->destroyEntity(t_ent); }
  bullet->body->setPosition({bullet->pos.x, bullet->pos.y});
}
