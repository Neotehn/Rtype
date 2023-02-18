#ifndef R_TYPE_CLIENT_INIT_HPP
#define R_TYPE_CLIENT_INIT_HPP

#include "../ECS/EntityManager.hpp"
#include "../../Server/Protocol/UdpServer.hpp"
#include "../Encapsulation/GraphicDataTypes.hpp"
#include "../Encapsulation/IRectangleShape.hpp"
#include "../Encapsulation/SFML/RectangleShape.hpp"

void initPlayer(EntityManager &t_entity_manager, UdpServer *t_serverCom);
void initEnemy();
void initBullet();
void initBackground(EntityManager &t_entity_manager);
Health initPlayerHealthBar(EntityManager &t_entity_manager);

#endif  //R_TYPE_CLIENT_INIT_HPP
