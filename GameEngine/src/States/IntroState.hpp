#ifndef RTYPE_INTROSTATE_HPP
#define RTYPE_INTROSTATE_HPP

#include "../../../Game/Encapsulation/IRenderWindow.hpp"
#include "../../../Game/Encapsulation/ITexture.hpp"
#include "../../../Game/Encapsulation/ISprite.hpp"

#include "./MainState.hpp"
#include "../Button.hpp"
#include "../State.hpp"
#include "../StateMachine.hpp"

class IntroState final : public State {
 public:
  IntroState(StateMachine &t_machine, rtype::IRenderWindow *t_window,
                MusicPlayer &t_music_player, std::size_t t_flag,
                rtype::IGraphicLoader *t_graphic_loader, int *t_level,
                bool t_replace = true);
  ~IntroState();
  void pause() override;
  void resume() override;
  void update() override;
  void draw() override;
  void animateAndMoveShip();
  void checkCollisionAngle(rtype::Vector2f collisionNormal);

 private:
  rtype::ITexture *m_bg_t;
  rtype::ISprite *m_bg_s;
  Button m_start_btn;
  std::size_t m_flag;
  rtype::ITexture *m_spaceship_t;
  rtype::ISprite *m_spaceship_s;
  rtype::Vector2f m_spaceMovement;
};

#endif  //RTYPE_INTROSTATE_HPP
