#ifndef R_TYPE_CLIENT_CREATEOBJECTSYSTEM_HPP
#define R_TYPE_CLIENT_CREATEOBJECTSYSTEM_HPP

#include <memory>
#include <string>

#include "../CreateEntities/Init.hpp"
#include "../ECS/ISystem.hpp"
#include "../ECS/DataTypesECS.hpp"
#include "./AnimationSystem.hpp"
#include "./SoundSystem.hpp"

class CreateObjectSystem : public ISystem {
 public:
  CreateObjectSystem(std::shared_ptr<EntityManager> t_em,
                     std::vector<SoundSystem::SoundType> &t_sounds,
                     rtype::IGraphicLoader *t_graphic_loader);
  ~CreateObjectSystem();

  void update();
  void updateData(SystemData &t_data);

 private:
  std::shared_ptr<EntityManager> m_em;
  EventQueue m_event_queue;
  std::vector<SoundSystem::SoundType> &m_play_sounds;
  rtype::IGraphicLoader *m_graphic_loader;

  void createPlayer(EntityID t_id, std::string t_sprite_path,
                    rtype::Vector2f t_pos, int t_player_id);
  Health initPlayerHealthBar(EntityID t_player_id);
  void createBullet(EntityID t_id, rtype::Vector2f t_pos,
                    Action::ShootingType t_shooting_type);
  void createEnemy(EntityID t_id, rtype::Vector2f t_pos, float velocity);
  void createExplosion(EntityID t_id, rtype::Vector2f t_pos);
  void createPowerUp(EntityID t_id, rtype::Vector2f t_pos);
  void createItem(EntityID t_id, rtype::ItemType t_item_type,
                  rtype::Vector2f t_pos);
};

#endif  //R_TYPE_CLIENT_CREATEOBJECTSYSTEM_HPP
