#ifndef SETTINGSSTATE_HPP_
#define SETTINGSSTATE_HPP_

#include <iostream>

#include "../../../Game/Encapsulation/IRenderWindow.hpp"
#include "../../../Game/Encapsulation/ITexture.hpp"
#include "../../../Game/Encapsulation/ISprite.hpp"
#include "../../../Game/Encapsulation/IFont.hpp"
#include "../../../Game/Encapsulation/IText.hpp"

#include "./MainState.hpp"
#include "../MusicPlayer.hpp"
#include "../Button.hpp"
#include "../State.hpp"
#include "../StateMachine.hpp"

class SettingsState final : public State {
 public:
  SettingsState(StateMachine &t_machine, rtype::IRenderWindow *t_window,
                MusicPlayer &t_music_player, std::size_t t_flag,
                rtype::IGraphicLoader *t_graphic_loader, int *t_level,
                bool t_replace = true, std::string t_ip = "",
                UdpClient *t_clientCom = nullptr);
  ~SettingsState();
  void pause() override;
  void resume() override;
  void update() override;
  void draw() override;

 private:
  rtype::ITexture *m_bg_t;
  rtype::ISprite *m_bg_s;
  Button m_start_btn;
  Button m_vol_up;
  Button m_vol_down;
  rtype::IFont *m_font;
  rtype::IText *m_title;
  rtype::IText *m_vol_txt;

  std::size_t m_flag;
};

#endif  // !SETTINGSSTATE_HPP_
