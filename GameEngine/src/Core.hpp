#ifndef CORE_HPP_
#define CORE_HPP_

#include "../../Game/Encapsulation/IRenderWindow.hpp"
#include "../../Game/Encapsulation/IGraphicLoader.hpp"
#include "../../Game/Encapsulation/SFML/GraphicLoader.hpp"
#include "../../Game/Encapsulation/raylib/RaylibGraphicLoader.hpp"
#include "./States/MainState.hpp"
#include "./MusicPlayer.hpp"
#include "./StateMachine.hpp"
#include "./States/IntroState.hpp"
#include "../../Client/Protocol/UdpClient.hpp"
#include "../../Server/Protocol/UdpServer.hpp"

class Core {
 public:
  Core(std::size_t t_flag, std::string t_ip, const std::string &t_path,
       int *t_level);
  ~Core();
  Core(const Core &);
  void run();

 private:
  rtype::IRenderWindow *m_window;
  StateMachine m_state_machine;
  MusicPlayer m_music_player;
  rtype::IGraphicLoader *m_graphic_loader;
  UdpClient *m_clientCom = nullptr;
  std::size_t m_port_number;
  boost::asio::io_service m_io_service;
};

#endif  // !CORE_HPP_
