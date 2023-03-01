#ifndef MAINSTATE_HPP_
#define MAINSTATE_HPP_

#include <iostream>

#include "../../../Game/Encapsulation/ITexture.hpp"
#include "../../../Game/Encapsulation/ISprite.hpp"

#include "../Button.hpp"
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
            bool t_replace = true);
  ~MainState();
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
  bool m_start_pressed;
};

#endif  //!MAINSTATE_HPP_
