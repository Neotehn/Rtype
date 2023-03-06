#include "SoundSystem.hpp"

SoundSystem::SoundSystem(std::shared_ptr<EntityManager> t_em,
                         std::vector<SoundType> &t_sounds,
                         rtype::IGraphicLoader *t_graphic_loader)
    : m_play_sounds(t_sounds) {
  m_em = t_em;
  m_graphic_loader = t_graphic_loader;
  // // init music
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

void SoundSystem::updateData(SystemData &t_data) { m_vol = t_data.volume; }

void SoundSystem::update() {
  std::cout << "sound" << std::endl;
  for (SoundType sound : m_play_sounds) {
    m_sounds->setVolume(sound, m_vol);
    m_sounds->play(sound);
  }
  m_play_sounds.clear();
}
