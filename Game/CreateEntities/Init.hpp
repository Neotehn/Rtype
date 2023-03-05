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
               bool t_play_music = true, UdpServer *t_server_com = nullptr);

void loadMap(std::shared_ptr<EntityManager> t_entity_manager,
             rtype::IGraphicLoader *t_graphic_loader, UdpServer *t_server_com);

EntityID initPlayer(std::shared_ptr<EntityManager> t_entity_manager,
                    UdpServer *t_serverCom,
                    rtype::IGraphicLoader *t_graphic_loader);

void initPlayerClient(EntityID t_id, std::string t_sprite_path,
                      rtype::Vector2f t_pos,
                      std::shared_ptr<EntityManager> t_entity_manager,
                      rtype::IGraphicLoader *t_graphic_loader, int t_player_id);
Health initPlayerHealthBar(rtype::IGraphicLoader *t_graphic_loader);

void initBulletClient(EntityID t_id, rtype::Vector2f t_pos,
                      std::shared_ptr<Action> t_action,
                      std::shared_ptr<EntityManager> t_em,
                      rtype::IGraphicLoader *t_graphic_loader,
                      EntityID t_owner_id);

void initEnemy(std::shared_ptr<EntityManager> t_em,
               rtype::IGraphicLoader *t_graphic_loader, UdpServer *t_serverCom,
               rtype::Vector2f t_pos = rtype::Vector2f{0, 0}, int t_health = 2);
void initEnemyClient(EntityID t_id, rtype::Vector2f t_pos, float t_velocity,
                     std::shared_ptr<EntityManager> t_em,
                     rtype::IGraphicLoader *t_graphic_loader);
void initPayWall(std::shared_ptr<EntityManager> t_em,
                 rtype::IGraphicLoader *t_graphic_loader,
                 UdpServer *t_server_com);
void initPayWallClient(EntityID t_id, std::shared_ptr<EntityManager> t_em,
                       rtype::IGraphicLoader *t_graphic_loader);

void initExplosionClient(EntityID t_id, rtype::Vector2f t_pos,
                         std::shared_ptr<EntityManager> t_em,
                         rtype::IGraphicLoader *t_graphic_loader);

void createCoin(std::shared_ptr<EntityManager> t_em,
                rtype::IGraphicLoader *t_graphic_loader,
                UdpServer *t_server_com);
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
void initCoinShoot(std::shared_ptr<Action> t_action,
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

unsigned int initObstacle(std::shared_ptr<EntityManager> t_entity_manager,
                          rtype::IGraphicLoader *t_graphic_loader,
                          rtype::Vector2f t_pos, std::string t_sprite_path,
                          int t_total_width, UdpServer *t_server_com);
void initObstacleClient(std::shared_ptr<EntityManager> t_entity_manager,
                        rtype::IGraphicLoader *t_graphic_loader,
                        rtype::Vector2f t_pos, std::string t_sprite_path,
                        int t_total_width, EntityID t_id);

bool loadNewEndboss(std::shared_ptr<EntityManager> t_em,
                    rtype::IGraphicLoader *t_graphic_loader,
                    UdpServer *t_server_com);
void initEndboss(std::shared_ptr<EntityManager> t_em,
                 rtype::IGraphicLoader *t_graphic_loader,
                 UdpServer *t_server_com, int t_nb);
void initEndbossClient(EntityID t_id, std::shared_ptr<EntityManager> t_em,
                       rtype::IGraphicLoader *t_graphic_loader);
#endif  //R_TYPE_CLIENT_INIT_HPP
