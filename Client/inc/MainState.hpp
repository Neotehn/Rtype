#ifndef MAINSTATE_HPP_
#define MAINSTATE_HPP_

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>

#include "../../GameEngine/inc/Button.hpp"
#include "../../GameEngine/inc/State.hpp"
#include "../../GameEngine/inc/StateMachine.hpp"

class MainState final : public State {
 public:
  MainState(StateMachine &t_machine, sf::RenderWindow &t_window,
            bool t_replace = true);
  void pause() override;
  void resume() override;
  void update() override;
  void draw() override;

 private:
  sf::Texture m_bg_t;
  sf::Sprite m_bg_s;
  Button m_start_btn;
  Button m_settings_btn;
};

#endif  //!MAINSTATE_HPP_
