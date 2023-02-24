#ifndef MUSICPLAYER_HPP_
#define MUSICPLAYER_HPP_

#include <iostream>
#include <map>

#include "../../Game/Encapsulation/SFML/Music.hpp"
#include "../../Game/Encapsulation/IMusic.hpp"

enum MusicID {
  MENU_THEME,
  MISSION_THEME,
};

class MusicPlayer {
 public:
  MusicPlayer();
  ~MusicPlayer();
  void play(MusicID t_theme);
  void stop();
  void setPaused(bool t_paused);
  void setVolume(float t_volume);
  float getVolume();

 private:
  rtype::IMusic *m_music;
  float m_volume;
};

#endif /* !MUSICPLAYER_HPP_ */
