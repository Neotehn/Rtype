#include "./Logger.hpp"

Logger::Logger() {
  auto time = std::chrono::system_clock::now();
  m_file.open("Logfiles/" +
              std::to_string(std::chrono::duration_cast<std::chrono::seconds>(
                               time.time_since_epoch())
                               .count()) +
              ".txt");
}

Logger::~Logger() { m_file.close(); }

void Logger::writeLog(Threatlevel t_threat_level, std::string t_message) {
  std::string threat_msg = "";

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
}