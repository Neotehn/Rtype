#ifndef R_TYPE_CLIENT_INIT_HPP
#define R_TYPE_CLIENT_INIT_HPP

#include "../ECS/EntityManager.hpp"

void initPlayer(EntityManager &t_entity_manager);
void initEnemy();
void initBullet();
void initBackground(EntityManager &t_entity_manager);
void initPlayerHealthBar(EntityManager &t_entity_manager);

#endif  //R_TYPE_CLIENT_INIT_HPP
