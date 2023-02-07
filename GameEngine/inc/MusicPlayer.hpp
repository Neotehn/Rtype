/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** MusicPlayer
*/

#ifndef MUSICPLAYER_HPP_
#define MUSICPLAYER_HPP_

#include <iostream>
#include <map>
#include <SFML/Audio.hpp>

enum MusicID {
  MENUTHEME,
  MISSIONTHEME,
};

class MusicPlayer {
 public:
  MusicPlayer();
  void play(MusicID t_theme);
  void stop();
  void setPaused(bool t_paused);
  void setVolume(float t_volume);
  float getVolume();

 private:
  sf::Music m_music;
  std::map<MusicID, std::string> m_filenames;
  float m_volume;
};

#endif /* !MUSICPLAYER_HPP_ */
