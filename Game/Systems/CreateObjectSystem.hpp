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
                     rtype::IGraphicLoader *t_graphic_loader,
                     const std::string &t_path_to_sprite);
  ~CreateObjectSystem() = default;

  void update() override;
  void updateData(SystemData &t_data) override;

 private:
  std::shared_ptr<EntityManager> m_em;
  EventQueue m_event_queue;
  std::vector<SoundSystem::SoundType> &m_play_sounds;
  rtype::IGraphicLoader *m_graphic_loader;
  std::string m_path_to_sprite;
};

#endif  //R_TYPE_CLIENT_CREATEOBJECTSYSTEM_HPP
