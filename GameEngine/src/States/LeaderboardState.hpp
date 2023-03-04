#ifndef R_TYPE_CLIENT_LEADERBOARDSTATE_HPP
#define R_TYPE_CLIENT_LEADERBOARDSTATE_HPP

#include "../../../Game/Encapsulation/IRenderWindow.hpp"
#include "../../../Game/Encapsulation/ITexture.hpp"
#include "../../../Game/Encapsulation/ISprite.hpp"

#include "../Button.hpp"
#include "../State.hpp"
#include "../StateMachine.hpp"
#include "./MainState.hpp"

class LeaderboardState : public State {
 public:
  LeaderboardState(StateMachine &t_machine, rtype::IRenderWindow *t_window,
             MusicPlayer &t_music_player, std::size_t t_flag,
             rtype::IGraphicLoader *t_graphic_loader, int *t_level,
             const std::string &t_path_to_sprite, bool t_replace = true,
             std::string t_ip = "", UdpClient *t_clientCom = nullptr);
  ~LeaderboardState();
  void pause() override;
  void resume() override;
  void update() override;
  void draw() override;
  void initSprites();
  void initText();

 private:
  rtype::ITexture *m_bg_t;
  rtype::ISprite *m_bg_s;
  Button m_next_btn;
  std::size_t m_flag;
  MusicPlayer m_sound_manager;
  rtype::IFont *m_font;
  rtype::IText *m_title;
  std::vector<rtype::IText *> m_leaderboard_list;
};

#endif  //R_TYPE_CLIENT_LEADERBOARDSTATE_HPP
