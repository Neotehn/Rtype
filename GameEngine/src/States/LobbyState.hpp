/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** LobbyState
*/

#ifndef LOBBYSTATE_HPP_
#define LOBBYSTATE_HPP_

#include <iostream>

#include "../../../Game/Encapsulation/ITexture.hpp"
#include "../../../Game/Encapsulation/SFML/Texture.hpp"
#include "../../../Game/Encapsulation/ISprite.hpp"
#include "../../../Game/Encapsulation/SFML/Sprite.hpp"
#include "../../../Game/Encapsulation/IFont.hpp"
#include "../../../Game/Encapsulation/SFML/Font.hpp"
#include "../../../Game/Encapsulation/IText.hpp"
#include "../../../Game/Encapsulation/SFML/Text.hpp"

#include "../Button.hpp"
#include "../MusicPlayer.hpp"
#include "../State.hpp"
#include "../StateMachine.hpp"
#include "./SettingsState.hpp"
#include "../../../Game/GameState.hpp"

class LobbyState final : public State {
 public:
  LobbyState(StateMachine &t_machine, rtype::IRenderWindow *t_window,
             MusicPlayer &t_music_player, std::size_t t_flag,
             bool t_replace = true);
  void pause() override;
  void resume() override;
  void update() override;
  void draw() override;

 private:
  rtype::ITexture *m_bg_t;
  rtype::ISprite *m_bg_s;
  Button m_start_btn;
  Button m_settings_btn;
  std::size_t m_flag;
  rtype::Font *m_font;
  rtype::Text *m_title;
};

#endif /* !LOBBYSTATE_HPP_ */
