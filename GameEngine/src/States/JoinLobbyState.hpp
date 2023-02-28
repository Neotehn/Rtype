/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** JoinLobbyState
*/

#ifndef JOINLOBBYSTATE_HPP_
#define JOINLOBBYSTATE_HPP_

#include <iostream>

#include "../../../Game/Encapsulation/ITexture.hpp"
#include "../../../Game/Encapsulation/ISprite.hpp"
#include "../../../Game/Encapsulation/IFont.hpp"
#include "../../../Game/Encapsulation/IText.hpp"

#include "../Button.hpp"
#include "../MusicPlayer.hpp"
#include "../State.hpp"
#include "../StateMachine.hpp"
#include "../Textbox.hpp"
#include "../../../Game/GameState.hpp"

class JoinLobbyState final : public State {
 public:
  JoinLobbyState(StateMachine &t_machine, rtype::IRenderWindow *t_window,
                 MusicPlayer &t_music_player, std::size_t t_flag,
                 rtype::IGraphicLoader *t_graphic_loader, int *t_level,
                 bool t_replace = true);
  void pause() override;
  void resume() override;
  void update() override;
  void draw() override;

 private:
  rtype::ITexture *m_bg_t;
  rtype::ISprite *m_bg_s;
  Button m_home_btn;
  Button m_start_btn;
  std::size_t m_flag;
  rtype::IFont *m_font;
  rtype::IText *m_title;
  rtype::ITexture *m_player_one_t;
  rtype::ITexture *m_player_two_t;
  rtype::ITexture *m_player_three_t;
  rtype::ITexture *m_player_four_t;
  rtype::ISprite *m_player_one_s;
  rtype::ISprite *m_player_two_s;
  rtype::ISprite *m_player_three_s;
  rtype::ISprite *m_player_four_s;
  Textbox m_textbox;
};

#endif /* !JOINLOBBYSTATE_HPP_ */
