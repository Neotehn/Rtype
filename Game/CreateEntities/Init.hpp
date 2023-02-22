#ifndef R_TYPE_CLIENT_INIT_HPP
#define R_TYPE_CLIENT_INIT_HPP

#include "../ECS/EntityManager.hpp"
#include "../../Server/Protocol/UdpServer.hpp"
#include "../Encapsulation/GraphicDataTypes.hpp"
#include "../Encapsulation/IRectangleShape.hpp"
#include "../Encapsulation/SFML/RectangleShape.hpp"

EntityID initPlayer(std::shared_ptr<EntityManager> t_entity_manager,
                    UdpServer *t_serverCom);
void initEnemy();
void initBullet();
void initBackground(EntityManager &t_entity_manager);
Health initPlayerHealthBar();

#endif  //R_TYPE_CLIENT_INIT_HPP
