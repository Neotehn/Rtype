#include "./Music.hpp"

rtype::Music::~Music() { m_music.stop(); };

bool rtype::Music::openFromFile(const std::string &t_path) {
  return m_music.openFromFile(t_path);
}

void rtype::Music::setVolume(float t_volume) { m_music.setVolume(t_volume); }

void rtype::Music::setLoop(bool t_loop) { m_music.setLoop(t_loop); }

void rtype::Music::play() { m_music.play(); }

void rtype::Music::stop() { m_music.stop(); }

void rtype::Music::pause() { m_music.pause(); }
