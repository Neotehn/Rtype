#ifndef SETTINGSSTATE_HPP_
#define SETTINGSSTATE_HPP_

#include <iostream>

#include "../../../Game/Encapsulation/IRenderWindow.hpp"
#include "../../../Game/Encapsulation/ITexture.hpp"
#include "../../../Game/Encapsulation/SFML/Texture.hpp"
#include "../../../Game/Encapsulation/ISprite.hpp"
#include "../../../Game/Encapsulation/SFML/Sprite.hpp"

#include "./MainState.hpp"
#include "../Button.hpp"
#include "../State.hpp"
#include "../StateMachine.hpp"

class SettingsState final : public State {
 public:
  SettingsState(StateMachine &t_machine, rtype::IRenderWindow *t_window,
                MusicPlayer &t_music_player, std::size_t t_flag,
                std::string t_address, bool t_replace = true);
  void pause() override;
  void resume() override;
  void update() override;
  void draw() override;

 private:
  rtype::ITexture *m_bg_t;
  rtype::ISprite *m_bg_s;
  Button m_start_btn;
  std::size_t m_flag;
  std::string m_address;
};

#endif  // !SETTINGSSTATE_HPP_
