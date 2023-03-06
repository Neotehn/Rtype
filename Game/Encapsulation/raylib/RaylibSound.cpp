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
    m_volume.push_back(0);
    return true;
  }

  void RaylibSound::play(int t_index) { PlaySound(m_sound[t_index]); }

  void RaylibSound::stop(int t_index) { StopSound(m_sound[t_index]); }

  void RaylibSound::pause(int t_index) { PauseSound(m_sound[t_index]); }

  void RaylibSound::setVolume(float t_volume) {
    int i = 0;
    for (auto &sound : m_sound) {
      SetSoundVolume(sound, t_volume);
      m_volume[i] = t_volume;
      i++;
    }
  }

  float RaylibSound::getVolume(int t_index) { return m_volume[t_index]; }

  void RaylibSound::setVolume(int t_index, float t_vol) {
    SetSoundVolume(m_sound[t_index], t_vol);
    m_volume[t_index] = t_vol;
  }
}  // namespace rtype
