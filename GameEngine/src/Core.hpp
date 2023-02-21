#ifndef CORE_HPP_
#define CORE_HPP_

#include "../../Game/Encapsulation/IRenderWindow.hpp"
#include "../../Game/Encapsulation/SFML/RenderWindow.hpp"
#include "./States/MainState.hpp"
#include "./MusicPlayer.hpp"
#include "./StateMachine.hpp"

class Core {
 public:
  Core(std::size_t t_flag);
  Core(std::size_t t_flag, std::string t_address);
  ~Core();
  Core(const Core &);
  void run();

 private:
  rtype::IRenderWindow *m_window;
  StateMachine m_state_machine;
  MusicPlayer m_music_player;
};

#endif  // !CORE_HPP_
