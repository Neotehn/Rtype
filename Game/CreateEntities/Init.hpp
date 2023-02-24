#ifndef R_TYPE_CLIENT_INIT_HPP
#define R_TYPE_CLIENT_INIT_HPP

#include "../ECS/EntityManager.hpp"
#include "../../Server/Protocol/UdpServer.hpp"
#include "../Encapsulation/GraphicDataTypes.hpp"
#include "../Encapsulation/IRectangleShape.hpp"
#include "../Encapsulation/IGraphicLoader.hpp"

EntityID initPlayer(std::shared_ptr<EntityManager> t_entity_manager,
                    UdpServer *t_serverCom,
                    rtype::IGraphicLoader *t_graphic_loader);
void initEnemy();
void initBullet();
void initBackground(EntityManager &t_entity_manager,
                    rtype::IGraphicLoader *t_graphic_loader);
Health initPlayerHealthBar(rtype::IGraphicLoader *t_graphic_loader);

#endif  //R_TYPE_CLIENT_INIT_HPP
