#ifndef R_TYPE_CLIENT_INIT_HPP
#define R_TYPE_CLIENT_INIT_HPP

#include "../../Server/Protocol/UdpServer.hpp"
#include "../ECS/EntityManager.hpp"
#include "../Encapsulation/GraphicDataTypes.hpp"
#include "../Encapsulation/IGraphicLoader.hpp"
#include "../Encapsulation/IMusic.hpp"
#include "../Encapsulation/IRectangleShape.hpp"
#include "./AssetLoader.hpp"

void loadLevel(int t_level);

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
                      std::shared_ptr<EntityManager> m_em,
                      rtype::IGraphicLoader *m_graphic_loader);

void initEnemy(std::shared_ptr<EntityManager> m_em,
               rtype::IGraphicLoader *m_graphic_loader, UdpServer *m_serverCom);
void initEnemyClient(EntityID t_id, rtype::Vector2f t_pos, float t_velocity,
                     std::shared_ptr<EntityManager> m_em,
                     rtype::IGraphicLoader *m_graphic_loader);

void initExplosionClient(EntityID t_id, rtype::Vector2f t_pos,
                         std::shared_ptr<EntityManager> m_em,
                         rtype::IGraphicLoader *m_graphic_loader);

void initPowerUp(std::shared_ptr<EntityManager> m_em,
                 rtype::IGraphicLoader *m_graphic_loader,
                 UdpServer *m_serverCom);
void initPowerUpClient(EntityID t_id, rtype::Vector2f t_pos,
                       std::shared_ptr<EntityManager> m_em,
                       rtype::IGraphicLoader *m_graphic_loader);

void initItemClient(EntityID t_id, rtype::ItemType t_item_type,
                    rtype::Vector2f t_pos, std::shared_ptr<EntityManager> m_em,
                    rtype::IGraphicLoader *m_graphic_loader);

void initShoot(std::shared_ptr<Action> action,
               std::shared_ptr<EntityManager> m_em,
               rtype::IGraphicLoader *m_graphic_loader, UdpServer *m_serverCom);
void initFireShoot(std::shared_ptr<Action> action,
                   std::shared_ptr<EntityManager> m_em,
                   rtype::IGraphicLoader *m_graphic_loader,
                   UdpServer *m_serverCom);
void initBombShoot(std::shared_ptr<Action> action,
                   std::shared_ptr<EntityManager> m_em,
                   rtype::IGraphicLoader *m_graphic_loader,
                   UdpServer *m_serverCom);

void loadMusic(rtype::IMusic *m_music);

void initBackground(EntityManager &t_entity_manager,
                    rtype::IGraphicLoader *t_graphic_loader);

#endif  //R_TYPE_CLIENT_INIT_HPP
