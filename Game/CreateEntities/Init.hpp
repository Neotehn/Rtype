#ifndef R_TYPE_CLIENT_INIT_HPP
#define R_TYPE_CLIENT_INIT_HPP

#include "../ECS/EntityManager.hpp"
#include "../../Server/Protocol/UdpServer.hpp"

void initPlayer(EntityManager &t_entity_manager, UdpServer *t_serverCom);
void initEnemy();
void initBullet();
void initBackground(EntityManager &t_entity_manager);
void initPlayerHealthBar(EntityID t_player_id, EntityManager &t_entity_manager);

#endif  //R_TYPE_CLIENT_INIT_HPP
