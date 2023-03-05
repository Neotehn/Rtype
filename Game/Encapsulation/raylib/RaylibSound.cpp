#include "RaylibSound.hpp"

namespace rtype {
  RaylibSound::~RaylibSound() {
    for (auto &sound : m_sound) {
      UnloadSound(sound);
    }
  }

  bool RaylibSound::addSoundFromFile(const std::string &t_path) {
    Sound sound = LoadSound(t_path.c_str());
    m_sound.push_back(sound);
    return true;
  }

  void RaylibSound::play(int t_index) { PlaySound(m_sound[t_index]); }

  void RaylibSound::stop(int t_index) { StopSound(m_sound[t_index]); }

  void RaylibSound::pause(int t_index) { PauseSound(m_sound[t_index]); }

  void RaylibSound::setVolume(float t_volume) {
    for (auto &sound : m_sound) {
      SetSoundVolume(sound, t_volume);
    }
  }
}  // namespace rtype
