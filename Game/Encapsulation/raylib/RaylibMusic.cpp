#include "RaylibMusic.hpp"

rtype::RaylibMusic::~RaylibMusic() {
  for (Music music : m_music) {
    StopMusicStream(music);
    UnloadMusicStream(music);
  }
}

bool rtype::RaylibMusic::openFromFile(const std::string &t_path) {
  Music music = LoadMusicStream(t_path.c_str());
  m_music.push_back(music);
  return true;
}

void rtype::RaylibMusic::setVolume(float t_volume) {
  for (Music music : m_music)
    SetMusicVolume(music, t_volume);
}

void rtype::RaylibMusic::setLoop(bool t_loop) {}

void rtype::RaylibMusic::play(int index) {
  if (index < 0 || index >= m_music.size()) {
    std::cout << "Error while playing music" << std::endl;
    return;
  }
  PlayMusicStream(m_music[index]);
}

void rtype::RaylibMusic::stop() {
  for (Music music : m_music)
    StopMusicStream(music);
}

void rtype::RaylibMusic::pause() {
  for (Music music : m_music)
    PauseMusicStream(music);
}
