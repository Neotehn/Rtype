#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "../../GameEngine/inc/State.hpp"

class StateMachine;

namespace sf {
class RenderWindow;
}

class PlayState final : public State {
 public:
  PlayState(StateMachine &machine, sf::RenderWindow &window,
            bool replace = true);

  void pause() override;
  void resume() override;

  void update() override;
  void draw() override;

 private:
  sf::Texture m_backgroundTexture;
  sf::Sprite m_background;
};