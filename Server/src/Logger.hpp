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
  void openFile();
  void closeFile();

 private:
  std::ofstream m_file;
  std::string m_file_name;
};

#endif  //R_TYPE_SERVER_LOGGER_HPP