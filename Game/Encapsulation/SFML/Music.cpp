#include "./Music.hpp"

rtype::Music::~Music() {
  for (sf::Music *music : m_music) {
    music->stop();
    delete music;
  }
};

bool rtype::Music::openFromFile(const std::string &t_path) {
  sf::Music *music = new sf::Music();
  bool res = music->openFromFile(t_path);
  m_music.push_back(music);
  return res;
}

void rtype::Music::setVolume(float t_volume) {
  for (sf::Music *music : m_music)
    music->setVolume(t_volume);
}

void rtype::Music::setLoop(bool t_loop) {
  for (sf::Music *music : m_music) {
    music->setLoop(t_loop);
  }
}

void rtype::Music::play(int index) {
  if (index < 0 || index >= m_music.size()) {
    std::cout << "Error while playing music" << std::endl;
    return;
  }
  m_music[index]->play();
}

void rtype::Music::stop() {
  for (sf::Music *music : m_music)
    music->stop();
}

void rtype::Music::pause() {
  for (sf::Music *music : m_music)
    music->pause();
}
