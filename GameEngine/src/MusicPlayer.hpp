#ifndef MUSICPLAYER_HPP_
#define MUSICPLAYER_HPP_

#include <iostream>
#include <map>

#include "../../Game/Encapsulation/IMusic.hpp"
#include "../../Game/Encapsulation/IGraphicLoader.hpp"

enum MusicID {
  MENU_THEME,
  MISSION_THEME,
};

class MusicPlayer {
 public:
  MusicPlayer();
  ~MusicPlayer();
  void init(rtype::IGraphicLoader *t_graphic_loader);
  void play(MusicID t_theme);
  void stop();
  void setPaused(bool t_paused);
  void setVolume(float t_volume);

 private:
  rtype::IMusic *m_music;
  float m_volume;
  rtype::IGraphicLoader *m_graphic_loader;
};

#endif /* !MUSICPLAYER_HPP_ */
