#ifndef CORE_HPP_
#define CORE_HPP_

#include <SFML/Graphics/RenderWindow.hpp>

#include "MusicPlayer.hpp"
#include "StateMachine.hpp"

class Core {
 public:
  Core(std::size_t t_flag);
  ~Core();
  Core(const Core &);
  void run();

 private:
  sf::RenderWindow m_window;
  StateMachine m_state_machine;
  MusicPlayer m_music_player;
};

#endif  // !CORE_HPP_
