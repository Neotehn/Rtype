#ifndef R_TYPE_CLIENT_INIT_HPP
#define R_TYPE_CLIENT_INIT_HPP

#include "../../Server/Protocol/UdpServer.hpp"
#include "../ECS/EntityManager.hpp"
#include "../ECS/EntityViewer.hpp"
#include "../Encapsulation/GraphicDataTypes.hpp"
#include "../Encapsulation/IGraphicLoader.hpp"
#include "../Encapsulation/IMusic.hpp"
#include "../Encapsulation/IRectangleShape.hpp"
#include "./AssetLoader.hpp"

bool loadLevel(int *t_level, std::shared_ptr<EntityManager> t_entity_manager,
               rtype::IGraphicLoader *t_graphic_loader, rtype::IMusic *t_music,
               bool t_play_music = true);

EntityID initPlayer(std::shared_ptr<EntityManager> t_entity_manager,
                    UdpServer *t_serverCom,
                    rtype::IGraphicLoader *t_graphic_loader);
void initPlayerClient(EntityID t_id, std::string t_sprite_path,
                      rtype::Vector2f t_pos,
                      std::shared_ptr<EntityManager> t_entity_manager,
                      rtype::IGraphicLoader *t_graphic_loader);
Health initPlayerHealthBar(rtype::IGraphicLoader *t_graphic_loader);

void initBulletClient(EntityID t_id, rtype::Vector2f t_pos,
                      Action::ShootingType t_shooting_type,
                      std::shared_ptr<EntityManager> t_em,
                      rtype::IGraphicLoader *t_graphic_loader,
                      EntityID t_owner_id);

void initEnemy(std::shared_ptr<EntityManager> t_em,
               rtype::IGraphicLoader *t_graphic_loader, UdpServer *t_serverCom);
void initEnemyClient(EntityID t_id, rtype::Vector2f t_pos, float t_velocity,
                     std::shared_ptr<EntityManager> t_em,
                     rtype::IGraphicLoader *t_graphic_loader);

void initExplosionClient(EntityID t_id, rtype::Vector2f t_pos,
                         std::shared_ptr<EntityManager> t_em,
                         rtype::IGraphicLoader *t_graphic_loader);

void initPowerUp(std::shared_ptr<EntityManager> t_em,
                 rtype::IGraphicLoader *t_graphic_loader,
                 UdpServer *t_server_com);
void initPowerUpClient(EntityID t_id, rtype::Vector2f t_pos,
                       std::shared_ptr<EntityManager> t_em,
                       rtype::IGraphicLoader *t_graphic_loader);

void initItemClient(EntityID t_id, rtype::ItemType t_item_type,
                    rtype::Vector2f t_pos, std::shared_ptr<EntityManager> t_em,
                    rtype::IGraphicLoader *t_graphic_loader);

void initShoot(std::shared_ptr<Action> t_action,
               std::shared_ptr<EntityManager> t_em,
               rtype::IGraphicLoader *t_graphic_loader,
               UdpServer *t_server_com);
void initFireShoot(std::shared_ptr<Action> t_action,
                   std::shared_ptr<EntityManager> t_em,
                   rtype::IGraphicLoader *t_graphic_loader,
                   UdpServer *t_server_com);
void initBombShoot(std::shared_ptr<Action> t_action,
                   std::shared_ptr<EntityManager> t_em,
                   rtype::IGraphicLoader *t_graphic_loader,
                   UdpServer *t_server_com);

void loadMusic(rtype::IMusic *t_music, bool t_play = true);

void initBackground(std::shared_ptr<EntityManager> t_em,
                    rtype::IGraphicLoader *t_graphic_loader);

#endif  //R_TYPE_CLIENT_INIT_HPP
