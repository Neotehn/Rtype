#ifndef CORE_HPP_
#define CORE_HPP_

#include "../../Game/Encapsulation/IRenderWindow.hpp"
#include "../../Game/Encapsulation/IGraphicLoader.hpp"
#include "../../Game/Encapsulation/SFML/GraphicLoader.hpp"
#include "./States/MainState.hpp"
#include "./MusicPlayer.hpp"
#include "./StateMachine.hpp"

class Core {
 public:
  Core(std::size_t t_flag, std::string t_ip);
  ~Core();
  Core(const Core &);
  void run();

 private:
  rtype::IRenderWindow *m_window;
  StateMachine m_state_machine;
  MusicPlayer m_music_player;
  rtype::IGraphicLoader *m_graphic_loader;
};

#endif  // !CORE_HPP_
