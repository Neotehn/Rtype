#ifndef MAINSTATE_HPP_
#define MAINSTATE_HPP_

#include <iostream>

#include "../../../Game/Encapsulation/ITexture.hpp"
#include "../../../Game/Encapsulation/ISprite.hpp"
#include "../../../Game/Encapsulation/IFont.hpp"
#include "../../../Game/Encapsulation/IText.hpp"

#include "../Button.hpp"
#include "./CreateLobbyState.hpp"
#include "./JoinLobbyState.hpp"
#include "../MusicPlayer.hpp"
#include "../State.hpp"
#include "../StateMachine.hpp"
#include "./SettingsState.hpp"
#include "IntroState.hpp"
#include "../../../Game/GameState.hpp"

class MainState final : public State {
 public:
  MainState(StateMachine &t_machine, rtype::IRenderWindow *t_window,
            MusicPlayer &t_music_player, std::size_t t_flag,
            rtype::IGraphicLoader *t_graphic_loader, int *t_level,
            bool t_replace = true, std::string t_ip = "",
            UdpClient *t_clientCom = nullptr);
  ~MainState();
  std::string createLobbyCode();
  void pause() override;
  void resume() override;
  void update() override;
  void draw() override;

 private:
  rtype::ITexture *m_bg_t;
  rtype::ISprite *m_bg_s;
  Button m_start_btn;
  Button m_settings_btn;
  Button m_exit_btn;
  Button m_join_btn;
  Button m_create_btn;
  rtype::IFont *m_font;
  rtype::IText *m_title;
  std::size_t m_flag;
  bool m_start_pressed;

  void initSprites();
  void initText();
  std::string m_path_to_sprite;
};

#endif  //!MAINSTATE_HPP_
