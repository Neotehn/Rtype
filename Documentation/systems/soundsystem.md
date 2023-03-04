# SoundSystem

The SoundSystem will play all game sounds, like shooting sounds, explosion sounds or a sound if you win or die.&#x20;

SoundSystem.hpp:

```
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
  rtype::ISounds *m_sounds;
  rtype::IGraphicLoader *m_graphic_loader;

  std::vector<SoundType> &m_play_sounds;
};

#endif  //R_TYPE_CLIENT_SOUNDSYSTEM_HPP
```

SoundSystem.cpp:

```
#include "SoundSystem.hpp"

SoundSystem::SoundSystem(std::shared_ptr<EntityManager> t_em,
                         std::vector<SoundType> &t_sounds,
                         rtype::IGraphicLoader *t_graphic_loader)
    : m_play_sounds(t_sounds) {
  m_em = t_em;
  m_graphic_loader = t_graphic_loader;

  // init music

  m_sounds = m_graphic_loader->loadSound();
  // init sounds - according to SoundType order
  m_sounds->addSoundFromFile("../Client/assets/sounds/shoot.wav");
  m_sounds->addSoundFromFile("../Client/assets/sounds/explosion.wav");
  m_sounds->addSoundFromFile("../Client/assets/sounds/powerup.ogg");
  m_sounds->addSoundFromFile("../Client/assets/sounds/death.wav");
  m_sounds->addSoundFromFile("../Client/assets/sounds/win.wav");
}

SoundSystem::~SoundSystem() {
  if (m_sounds) delete m_sounds;
}

void SoundSystem::updateData(SystemData &t_data) {}

void SoundSystem::update() {
  for (SoundType sound : m_play_sounds) {
    m_sounds->play(sound);
  }
  m_play_sounds.clear();
}
```

[Back](../game-engine/systems.md)
