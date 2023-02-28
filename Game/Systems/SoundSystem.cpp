#include "SoundSystem.hpp"

std::vector<std::string> splitstr2(std::string s, std::string delimiter) {
  size_t pos_start = 0, pos_end, delim_len = delimiter.length();
  std::string token;
  std::vector<std::string> res;
  while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
    token = s.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    res.push_back(token);
  }
  res.push_back(s.substr(pos_start));
  return res;
}

SoundSystem::SoundSystem(std::shared_ptr<EntityManager> t_em,
                         std::vector<SoundType> &t_sounds,
                         rtype::IGraphicLoader *t_graphic_loader)
    : m_play_sounds(t_sounds) {
  m_em = t_em;
  m_graphic_loader = t_graphic_loader;

  // std::ifstream file_read("./assets/files/settings.txt");
  // std::string settxt((std::istreambuf_iterator<char>(file_read)),
  //                    std::istreambuf_iterator<char>());
  // std::vector<std::string> v = splitstr2(settxt, ":");

  // // init music

  m_sounds = m_graphic_loader->loadSound();
  // m_sounds->setVolume(atof(v[1].c_str()));
  // init sounds - according to SoundType order
  m_sounds->addSoundFromFile("../Client/assets/sounds/shoot.wav");
  m_sounds->addSoundFromFile("../Client/assets/sounds/explosion.wav");
  m_sounds->addSoundFromFile("../Client/assets/sounds/powerup.ogg");
  m_sounds->addSoundFromFile("../Client/assets/sounds/death.wav");
  m_sounds->addSoundFromFile("../Client/assets/sounds/win.wav");
}

SoundSystem::~SoundSystem() { delete m_sounds; }

void SoundSystem::updateData(SystemData &t_data) {}

void SoundSystem::update() {
  for (SoundType sound : m_play_sounds) {
    m_sounds->play(sound);
  }
  m_play_sounds.clear();
}
