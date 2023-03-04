#ifndef STATE_HPP_
#define STATE_HPP_

#include <memory>

#include "../../Game/Encapsulation/GraphicDataTypes.hpp"
#include "../../Game/Encapsulation/IRenderWindow.hpp"
#include "../../Game/Encapsulation/IMouse.hpp"
#include "../../Game/Encapsulation/IGraphicLoader.hpp"
#include "./MusicPlayer.hpp"
#include "../../Client/Protocol/UdpClient.hpp"
#include "../../Server/Protocol/UdpServer.hpp"

class StateMachine;

class State {
 public:
  State(StateMachine &t_machine, rtype::IRenderWindow *t_window,
        MusicPlayer &t_music_player, rtype::IGraphicLoader *t_graphic_loader,
        int *t_level, const std::string &t_path_to_sprite,
        bool t_replace = true, std::string t_ip = "",
        UdpClient *t_clientCom = nullptr);

  virtual ~State() = default;

  State(const State &) = delete;
  State &operator=(const State &) = delete;

  virtual void update() = 0;
  virtual void draw() = 0;

  std::unique_ptr<State> next();

  const bool isReplacing();

 protected:
  StateMachine &m_state_machine;
  rtype::IRenderWindow *m_window;
  rtype::IMouse *m_mouse;
  MusicPlayer &m_music_player;
  UdpClient *m_clientCom = nullptr;
  bool m_replace;
  std::unique_ptr<State> m_next;
  rtype::IGraphicLoader *m_graphic_loader;
  int *m_level;
  std::string m_ip;
  std::string m_path_to_sprite;
};

#endif  // !STATE_HPP_
