#ifndef R_TYPE_SERVER_LOGGER_HPP
#define R_TYPE_SERVER_LOGGER_HPP

#include <string>
#include <chrono>
#include <iostream>
#include <fstream>

class Logger {
 public:
  enum Threatlevel { LOG, WARNING, ERROR };
  Logger();
  ~Logger();
  void writeLog(Threatlevel t_threat_level, std::string t_message);

 private:
  std::ofstream m_file;
};

#endif  //R_TYPE_SERVER_LOGGER_HPP