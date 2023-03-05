#ifndef R_TYPE_CLIENT_RAYLIBMUSIC_HPP
#define R_TYPE_CLIENT_RAYLIBMUSIC_HPP

#include <iostream>
#include <string>
#include <vector>

#include <raylib.h>

#include "../IMusic.hpp"

namespace rtype {
  class RaylibMusic : public IMusic {
   public:
    RaylibMusic() = default;
    ~RaylibMusic() override;

    bool openFromFile(const std::string &t_path) override;
    void setVolume(float t_volume) override;
    void setLoop(bool t_loop) override;
    void play(int index) override;
    void stop() override;
    void pause() override;

   private:
    std::vector<Music> m_music;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_RAYLIBMUSIC_HPP
