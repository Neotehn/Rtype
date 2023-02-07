/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** MusicPlayer
*/

#include "../inc/MusicPlayer.hpp"

MusicPlayer::MusicPlayer() : m_music(), m_filenames(), m_volume(100.f) {
  m_filenames[MusicID::MENUTHEME] = "./assets/music/music1.ogg";
  m_filenames[MusicID::MISSIONTHEME] = "./assets/music/music2.ogg";
}

void MusicPlayer::play(MusicID t_theme) {
  std::string filename = m_filenames[t_theme];
  if (!m_music.openFromFile(filename))
    throw std::runtime_error("Music " + filename + " could not be loaded.");
  m_music.setVolume(m_volume);
  m_music.setLoop(true);
  m_music.play();
}

void MusicPlayer::stop() { m_music.stop(); }
void MusicPlayer::setPaused(bool t_paused) {
  if (t_paused)
    m_music.pause();
  else
    m_music.play();
}

float MusicPlayer::getVolume() { return m_volume; }

void MusicPlayer::setVolume(float t_volume) {
  m_volume = t_volume;
  m_music.setVolume(m_volume);
}