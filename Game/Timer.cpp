#include "Timer.hpp"

Timer::Timer() { m_pause_time = 0; }

Timer::~Timer(){};

void Timer::startTimer() {
  m_pause_time = 0;
  m_start = std::chrono::system_clock::now();
}

float Timer::returnTime() {
  m_current_time = std::chrono::system_clock::now();
  std::chrono::duration<float> diff = m_current_time - m_start;
  float elapsedTime = diff.count() - m_pause_time;
  return elapsedTime;
}

void Timer::restartTimer() {
  m_pause_time = 0;
  m_start = std::chrono::system_clock::now();
}

//float Timer::returnAnimationTime() {
//    m_current_time = std::chrono::system_clock::now();
//    std::chrono::duration<float> diff = m_current_time - m_start;
//    float elapsedTime = diff.count() - m_pause_time - m_animation_time;
//    return elapsedTime;
//}

void Timer::startPause() { m_pause_start = std::chrono::system_clock::now(); }

void Timer::stopPause() {
  m_pause_end = std::chrono::system_clock::now();
  std::chrono::duration<float> diff = m_pause_end - m_pause_start;
  m_pause_time += diff.count();
}
