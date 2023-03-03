#ifndef R_TYPE_CLIENT_TIMER_HPP
#define R_TYPE_CLIENT_TIMER_HPP

#include <ctime>
#include <chrono>
#include <iostream>

class Timer {
 public:
  Timer();
  ~Timer();

  void startTimer();
  float returnTime();

  //  float returnAnimationTime();
  //  void setAnimationTime(float t_time);
  void restartTimer();
  void startPause();
  void stopPause();

 private:
  std::chrono::system_clock::time_point m_start;
  std::chrono::system_clock::time_point m_current_time;
  std::chrono::system_clock::time_point m_pause_start;
  std::chrono::system_clock::time_point m_pause_end;
  float m_pause_time;
};

#endif  //R_TYPE_CLIENT_TIMER_HPP