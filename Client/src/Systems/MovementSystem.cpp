/*
** EPITECH PROJECT, 2022
** .
** File description:
** .
*/
#include "MovementSystem.hpp"

MovementSystem::MovementSystem(std::shared_ptr<EntityManager> t_em) {
  m_em = t_em;
}

MovementSystem::~MovementSystem() {}

void MovementSystem::updateData(SystemData &t_data) {
  m_event_queue = t_data.event_queue;
}

void MovementSystem::update() {
  for (EntityID ent : EntityViewer<float, Pos, sf::RectangleShape>(*m_em.get())) {
    Pos* player = (*m_em.get()).Get<Pos>(ent);
    float* speed = (*m_em.get()).Get<float>(ent);
        sf::RectangleShape* body = (*m_em.get()).Get<sf::RectangleShape>(ent);
    sf::Vector2f direction = player->velocity;
    if (m_event_queue.checkIfKeyPressed(sf::Keyboard::A)) {
      direction.x = -1;
    }
    if (m_event_queue.checkIfKeyPressed(sf::Keyboard::D)) {
      direction.x = 1;
    }
    if (m_event_queue.checkIfKeyPressed(sf::Keyboard::W)) {
      direction.y = -1;
    }
    if (m_event_queue.checkIfKeyPressed(sf::Keyboard::S)) {
      direction.y = 1;
    }

    player->velocity = direction * *speed;
    std::cout << direction.x << " " << direction.y << std::endl;

    if (player->position.x <= body->getSize().x / 2) {
      player->velocity.x = 1;
    } else if (player->position.x + body->getSize().x >=
               800 + body->getSize().x / 2) {
      player->velocity.x = -1;
    }
    if (player->position.y <= body->getSize().y / 2) {
      player->velocity.y = 1;
    } else if (player->position.y + body->getSize().y >=
               1400 + body->getSize().y / 2) {
      player->velocity.y = -1;
    }
    player->position += player->velocity;
    body->setPosition(player->position);
    if (player->velocity.x != 0 || player->velocity.y != 0) player->velocity *= 0.99f;

  }

}
