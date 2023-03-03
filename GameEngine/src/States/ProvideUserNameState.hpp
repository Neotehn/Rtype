#ifndef R_TYPE_CLIENT_PROVIDEUSERNAMESTATE_HPP
#define R_TYPE_CLIENT_PROVIDEUSERNAMESTATE_HPP

#include <iostream>

#include "../../../Game/Encapsulation/ITexture.hpp"
#include "../../../Game/Encapsulation/ISprite.hpp"
#include "../../../Game/Encapsulation/IFont.hpp"
#include "../../../Game/Encapsulation/IText.hpp"

#include "../Button.hpp"
#include "../MusicPlayer.hpp"
#include "../State.hpp"
#include "../StateMachine.hpp"
#include "../Textbox.hpp"
#include "../../../Game/GameState.hpp"

class ProvideUserNameState final : public State {
 public:
  ProvideUserNameState(StateMachine &t_machine, rtype::IRenderWindow *t_window,
                       MusicPlayer &t_music_player, std::size_t t_flag,
                       rtype::IGraphicLoader *t_graphic_loader, int *t_level,
                       const std::string &t_path_to_sprite,
                       const std::string &t_player_name, bool t_replace = true,
                       std::string t_ip = "", UdpClient *t_clientCom = nullptr);
  void pause() override;
  void resume() override;
  void update() override;
  void draw() override;

 private:
  rtype::ITexture *m_bg_t;
  rtype::ISprite *m_bg_s;
  Button m_home_btn;
  std::size_t m_flag;
  rtype::IFont *m_font;
  rtype::IText *m_title;
  rtype::IText *m_instructions;
  Textbox m_textbox;
  bool m_is_pressed;
  void initSprites();
  void initText();
};

#endif  //R_TYPE_CLIENT_PROVIDEUSERNAMESTATE_HPP
