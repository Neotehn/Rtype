#include "Sounds.hpp"

rtype::Sounds::~Sounds() {
  for (sf::SoundBuffer *buffer : m_soundBuffer) {
    delete buffer;
  }
  for (sf::Sound sound : m_sound) {
    sound.stop();
  }
}

bool rtype::Sounds::addSoundFromFile(const std::string &t_path) {
  sf::SoundBuffer *buffer = new sf::SoundBuffer();

  if (!buffer->loadFromFile(t_path)) {
    std::cout << "Error while loading sound" << std::endl;
    return false;
  }
  m_soundBuffer.push_back(buffer);
  sf::Sound sound;
  sound.setBuffer(*m_soundBuffer.back());
  sound.setVolume(0);
  m_sound.push_back(sound);
  return true;
}

void rtype::Sounds::play(int t_index) {
  if (t_index < 0 || t_index >= m_sound.size()) {
    std::cout << "Error while playing sound" << std::endl;
    return;
  }
  m_sound[t_index].play();
}

void rtype::Sounds::stop(int t_index) {
  if (t_index < 0 || t_index >= m_sound.size()) {
    std::cout << "Error while stopping sound" << std::endl;
    return;
  }
  m_sound[t_index].stop();
}

void rtype::Sounds::pause(int t_index) {
  if (t_index < 0 || t_index >= m_sound.size()) {
    std::cout << "Error while pausing sound" << std::endl;
    return;
  }
  m_sound[t_index].pause();
}

void rtype::Sounds::setVolume(float t_volume) {
  for (sf::Sound sound : m_sound) {
    sound.setVolume(0);
  }
}

float rtype::Sounds::getVolume(int t_index) {
  if (t_index >= 0 && t_index < m_sound.size()) {
    return m_sound[t_index].getVolume();
  }
  return -1;
}

void rtype::Sounds::setVolume(int t_index, float t_volume) {
  if (t_index < 0 || t_index >= m_sound.size()) {
    std::cout << "Error while setting volume" << std::endl;
    return;
  }
  m_sound[t_index].setVolume(t_volume);
}