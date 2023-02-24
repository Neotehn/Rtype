# SoundSystem

The SoundSystem will play all game sounds, like shooting sounds, explosion sounds or a sound if you win or die.&#x20;

SoundSystem.hpp:

```
class SoundSystem : public ISystem {
 public:
  enum SoundType { shoot, explosion, power_up, death, won };
  SoundSystem(std::shared_ptr<EntityManager> t_em,
              std::vector<SoundType> &t_sounds);
  ~SoundSystem();

  virtual void update();
  virtual void updateData(SystemData &t_data);

 private:
  rtype::IMusic *m_music;
  rtype::ISounds *m_sounds;

  std::vector<SoundType> &m_play_sounds;
};
```

SoundSystem.cpp:

```
SoundSystem::SoundSystem(std::shared_ptr<EntityManager> t_em,
                         std::vector<SoundType> &t_sounds)
    : m_play_sounds(t_sounds) {
  m_em = t_em;
  m_music = new rtype::Music();

  // init music
  if (!m_music->openFromFile("../Client/assets/music/music2.ogg")) {
    std::cout << "Error while loading music" << std::endl;
  }
  m_music->setVolume(50);
  m_music->setLoop(true);
  m_music->play();

  m_sounds = new rtype::Sounds();
  // init sounds - according to SoundType order
  m_sounds->addSoundFromFile("../Client/assets/sounds/shoot.wav");
  m_sounds->addSoundFromFile("../Client/assets/sounds/explosion.wav");
  m_sounds->addSoundFromFile("../Client/assets/sounds/powerup.ogg");
  m_sounds->addSoundFromFile("../Client/assets/sounds/death.wav");
  m_sounds->addSoundFromFile("../Client/assets/sounds/win.wav");
}

SoundSystem::~SoundSystem() {
  delete m_music;
  delete m_sounds;
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
