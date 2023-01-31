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
  SettingsState(StateMachine &machine, sf::RenderWindow &window,
                bool replace = true);
  void pause() override;
  void resume() override;
  void update() override;
  void draw() override;

 private:
  sf::Texture m_bg_t;
  sf::Sprite m_bg_s;
  Button m_start_btn;
};

#endif  // !SETTINGSSTATE_HPP_
