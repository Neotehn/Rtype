#ifndef R_TYPE_CLIENT_RAYLIBSOUND_HPP
#define R_TYPE_CLIENT_RAYLIBSOUND_HPP

#include <iostream>
#include <string>

#include <raylib.h>

#include "../ISounds.hpp"

namespace rtype {
  class RaylibSound : public ISounds {
   public:
    RaylibSound() = default;
    ~RaylibSound();

    bool addSoundFromFile(const std::string &t_path) override;
    void play(int t_index) override;
    void stop(int t_index) override;
    void pause(int t_index) override;
    void setVolume(float t_volume) override;
    float getVolume(int t_index) override;
    void setVolume(int t_index, float t_vol) override;

   private:
    std::vector<Sound> m_sound;
    std::vector<float> m_volume = {};
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_RAYLIBSOUND_HPP
