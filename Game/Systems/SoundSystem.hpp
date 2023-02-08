#ifndef R_TYPE_CLIENT_SOUNDSYSTEM_HPP
#define R_TYPE_CLIENT_SOUNDSYSTEM_HPP

#include <memory>

#include <SFML/Audio.hpp>

#include "../ECS/ISystem.hpp"

class SoundSystem : public ISystem {
 public:
  enum SoundType { shoot, explosion, power_up, death, won };
  SoundSystem(std::shared_ptr<EntityManager> t_em,
              std::vector<SoundType> &t_sounds);
  ~SoundSystem();

  virtual void update();
  virtual void updateData(SystemData &t_data);

 private:
  sf::Music m_music;
  std::vector<sf::SoundBuffer *> m_sound_buffers;
  std::vector<sf::Sound> m_sounds;

  std::vector<SoundType> &m_play_sounds;

  void initSound(std::string path);
};

#endif  //R_TYPE_CLIENT_SOUNDSYSTEM_HPP
