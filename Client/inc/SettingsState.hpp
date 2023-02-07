#ifndef SETTINGSSTATE_HPP_
#define SETTINGSSTATE_HPP_

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>

#include "../../GameEngine/inc/Button.hpp"
#include "../../GameEngine/inc/State.hpp"
#include "../../GameEngine/inc/StateMachine.hpp"

class SettingsState final : public State {
 public:
  SettingsState(StateMachine &t_machine, sf::RenderWindow &t_window,
                MusicPlayer &t_music_player, bool t_replace = true);
  void pause() override;
  void resume() override;
  void update() override;
  void draw() override;

 private:
  sf::Texture m_bg_t;
  sf::Sprite m_bg_s;
  sf::Font m_font;
  sf::Text m_title;
  sf::Text m_vol_txt;
  Button m_start_btn;
  Button m_vol_up;
  Button m_vol_down;
};

#endif  // !SETTINGSSTATE_HPP_
