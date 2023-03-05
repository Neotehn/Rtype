#include "./MusicPlayer.hpp"

MusicPlayer::MusicPlayer() : m_volume(50.f) {}

MusicPlayer::~MusicPlayer() { delete m_music; }

std::vector<std::string> splitstr(std::string s, std::string delimiter) {
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

void MusicPlayer::init(rtype::IGraphicLoader *t_graphic_loader) {
  std::ifstream file_read("./assets/files/settings.txt");
  std::string settxt((std::istreambuf_iterator<char>(file_read)),
                     std::istreambuf_iterator<char>());
  std::vector<std::string> v = splitstr(settxt, ":");
  m_volume = atof(v[1].c_str());
  m_graphic_loader = t_graphic_loader;
  m_music = m_graphic_loader->loadMusic();
  m_music->openFromFile("./assets/music/music1.ogg");
  m_music->openFromFile("./assets/music/music2.ogg");
  m_music->openFromFile("./assets/music/moneySound.ogg");
  m_music->setLoop(true);
  m_music->setVolume(m_volume);
}

void MusicPlayer::init(rtype::IGraphicLoader *t_graphic_loader, bool t_loop) {
  m_graphic_loader = t_graphic_loader;
  m_music = m_graphic_loader->loadMusic();
  m_music->openFromFile("./assets/music/music1.ogg");
  m_music->openFromFile("./assets/music/music2.ogg");
  m_music->openFromFile("./assets/music/moneySound.ogg");
  m_music->setLoop(t_loop);
  m_music->setVolume(m_volume);
}

void MusicPlayer::play(MusicID t_theme) { m_music->play(t_theme); }

void MusicPlayer::stop() { m_music->stop(); }

void MusicPlayer::setPaused(bool t_paused) {
  if (t_paused)
    m_music->pause();
  else
    m_music->play();
}

float MusicPlayer::getVolume() { return m_volume; }

void MusicPlayer::setVolume(float t_volume) {
  m_volume = t_volume;
  m_music->setVolume(m_volume);
}