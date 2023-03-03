#include "./Logger.hpp"

Logger::Logger() {
  auto time = std::chrono::system_clock::now();
  m_file_name = "../Server/src/Logfiles/" +
                std::to_string(std::chrono::duration_cast<std::chrono::seconds>(
                                 time.time_since_epoch())
                                 .count()) +
                ".txt";
}

Logger::~Logger() { m_file.close(); }

void Logger::writeLog(Threatlevel t_threat_level, std::string t_message) {
  std::string threat_msg = "";
  openFile();
  switch (t_threat_level) {
    case Threatlevel::ERROR:
      threat_msg = "ERROR";
      break;
    case Threatlevel::LOG:
      threat_msg = "LOG";
      break;
    case Threatlevel::WARNING:
      threat_msg = "WARNING";
      break;

    default:
      threat_msg = "NO THREAT";
      break;
  }
  m_file << threat_msg << ": " << t_message << ".\n";
  closeFile();
}

void Logger::closeFile() { m_file.close(); }

void Logger::openFile() {
  m_file.open(m_file_name.c_str(), std::ios_base::app);
  if (!m_file) { std::cout << "Logger could not open the File" << std::endl; }
}