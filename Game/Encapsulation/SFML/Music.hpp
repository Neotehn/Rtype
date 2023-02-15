#ifndef R_TYPE_CLIENT_MUSIC_HPP
#define R_TYPE_CLIENT_MUSIC_HPP

#include <string>

#include <SFML/Audio.hpp>

#include "../IMusic.hpp"

namespace rtype {
  class Music : public IMusic {
   public:
    Music() = default;
    ~Music() override;

    bool openFromFile(const std::string &t_path) override;
    void setVolume(float t_volume) override;
    void setLoop(bool t_loop) override;
    void play() override;
    void stop() override;
    void pause() override;

   private:
    sf::Music m_music;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_MUSIC_HPP
