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
    sf::Vector2f direction = {0, 0};
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
    if (direction.x != 0 || direction.y != 0) {
      player->velocity = direction * *speed;
    }
    player->position += player->velocity;
    body->setPosition(player->position);
    if (player->velocity.x != 0 || player->velocity.y != 0) player->velocity *= 0.99f;
    std::cout << "Player position: " << player->position.x << " " << player->position.y << std::endl;
  }

}
