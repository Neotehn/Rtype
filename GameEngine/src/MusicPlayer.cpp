#include "./MusicPlayer.hpp"

MusicPlayer::MusicPlayer() : m_volume(50.f) {}

MusicPlayer::~MusicPlayer() { delete m_music; }

void MusicPlayer::init(rtype::IGraphicLoader *t_graphic_loader) {
  m_graphic_loader = t_graphic_loader;
  m_music = m_graphic_loader->loadMusic();
  m_music->openFromFile("./assets/music/music1.ogg");
  m_music->openFromFile("./assets/music/music2.ogg");
  m_music->setLoop(true);
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