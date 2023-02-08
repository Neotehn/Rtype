#include "SoundSystem.hpp"

SoundSystem::SoundSystem(std::shared_ptr<EntityManager> t_em,
                         std::vector<SoundType> &t_sounds)
    : m_play_sounds(t_sounds) {
  m_em = t_em;

  // init music
  if (!m_music.openFromFile("../Client/assets/music/music2.ogg")) {
    std::cout << "Error while loading music" << std::endl;
  }
  m_music.setVolume(50);
  m_music.setLoop(true);
  m_music.play();

  // init sounds - according to SoundType order
  initSound("../Client/assets/sounds/shoot.wav");
  initSound("../Client/assets/sounds/explosion.wav");
  initSound("../Client/assets/sounds/powerup.ogg");
  initSound("../Client/assets/sounds/death.wav");
  initSound("../Client/assets/sounds/win.wav");
}

SoundSystem::~SoundSystem() {
  m_music.stop();
  for (sf::SoundBuffer *buffer : m_sound_buffers) {
    delete buffer;
  }
  for (sf::Sound sound : m_sounds) {
    sound.stop();
  }
}

void SoundSystem::initSound(std::string path) {
  sf::SoundBuffer *buffer = new sf::SoundBuffer();
  if (!buffer->loadFromFile(path)) {
    std::cout << "Error while loading sound" << std::endl;
  }
  m_sound_buffers.push_back(buffer);
  sf::Sound sound;
  sound.setBuffer(*m_sound_buffers.back());
  m_sounds.push_back(sound);
}

void SoundSystem::updateData(SystemData &t_data) {}

void SoundSystem::update() {
  for (SoundType sound : m_play_sounds) {
    m_sounds[sound].play();
  }
  m_play_sounds.clear();
}
