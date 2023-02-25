#ifndef R_TYPE_CLIENT_SOUNDSYSTEM_HPP
#define R_TYPE_CLIENT_SOUNDSYSTEM_HPP

#include <memory>

#include "../CreateEntities/Init.hpp"
#include "../ECS/ISystem.hpp"
#include "../Encapsulation/IMusic.hpp"
#include "../Encapsulation/ISounds.hpp"

class SoundSystem : public ISystem {
 public:
  enum SoundType { shoot, explosion, power_up, death, won };
  SoundSystem(std::shared_ptr<EntityManager> t_em,
              std::vector<SoundType> &t_sounds,
              rtype::IGraphicLoader *t_graphic_loader);
  ~SoundSystem();

  virtual void update();
  virtual void updateData(SystemData &t_data);

 private:
  rtype::IMusic *m_music;
  rtype::ISounds *m_sounds;
  rtype::IGraphicLoader *m_graphic_loader;

  std::vector<SoundType> &m_play_sounds;
};

#endif  //R_TYPE_CLIENT_SOUNDSYSTEM_HPP
