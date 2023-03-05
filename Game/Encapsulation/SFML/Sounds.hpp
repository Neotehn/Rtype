#ifndef R_TYPE_CLIENT_SOUND_HPP
#define R_TYPE_CLIENT_SOUND_HPP

#include <iostream>
#include <string>

#include <SFML/Audio.hpp>

#include "../ISounds.hpp"

namespace rtype {
  class Sounds : public ISounds {
   public:
    Sounds() = default;
    ~Sounds();

    bool addSoundFromFile(const std::string &t_path) override;
    void play(int t_index) override;
    void stop(int t_index) override;
    void pause(int t_index) override;
    void setVolume(float t_volume) override;
    float getVolume(int t_index) override;
    void setVolume(int t_index, float t_volume);

   private:
    std::vector<sf::SoundBuffer *> m_soundBuffer;
    std::vector<sf::Sound> m_sound;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_SOUND_HPP
