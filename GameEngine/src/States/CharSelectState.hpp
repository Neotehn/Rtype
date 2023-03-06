/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** CharSelectState
*/

#ifndef CHARSELECTSTATE_HPP_
#define CHARSELECTSTATE_HPP_

#include <iostream>

#include "../../../Game/Encapsulation/ITexture.hpp"
#include "../../../Game/Encapsulation/ISprite.hpp"
#include "../../../Game/Encapsulation/IFont.hpp"
#include "../../../Game/Encapsulation/IText.hpp"

#include "../Button.hpp"
#include "../../../Game/GameState.hpp"
#include "../MusicPlayer.hpp"
#include "../State.hpp"
#include "../StateMachine.hpp"

class CharSelectState final : public State {
 public:
  CharSelectState(StateMachine &t_machine, rtype::IRenderWindow *t_window,
                  MusicPlayer &t_music_player, std::size_t t_flag,
                  rtype::IGraphicLoader *t_graphic_loader, int *t_level,
                  const std::string &t_path_to_sprite, bool t_replace = true,
                  std::string t_ip = "", UdpClient *t_clientCom = nullptr);
  ~CharSelectState();

  void update() override;
  void draw() override;

 private:
  rtype::ITexture *m_bg_t;
  rtype::ISprite *m_bg_s;
  rtype::IFont *m_font;
  rtype::IText *m_title;
  std::size_t m_flag;
  Button m_ship_blue;
  Button m_ship_green;
  Button m_ship_pink;
  Button m_ship_yellow;
  Button m_join_btn;
  bool m_is_pressed;
  std::string m_selected_ship;
  bool m_sel_blue;
  bool m_sel_green;
  bool m_sel_pink;
  bool m_sel_yellow;
  rtype::IRectangleShape *m_bg_selected;

  void initText();
  void initSprites();
};

#endif /* !CHARSELECTSTATE_HPP_ */
