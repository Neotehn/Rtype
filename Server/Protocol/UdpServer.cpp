#include "./UdpServer.hpp"

UdpServer::UdpServer(boost::asio::io_service &t_io_service,
                     InputManager &t_input_manager, bool &t_is_running,
                     std::string t_ip)
    : m_io_service(t_io_service), m_input_manager(t_input_manager),
      m_socket(
        t_io_service,
        udp::endpoint(boost::asio::ip::address::from_string(t_ip), 55555)),
      m_is_running(t_is_running),
      m_send_event_manager(t_input_manager.m_level) {
  m_flag = GameMode::none;
  m_logger.writeLog(Logger::Threatlevel::LOG, "Constructor");
  receiveClient();
  m_player_id_count = 0;
  m_start_time = std::chrono::system_clock::now();
  m_time_went_by = std::chrono::system_clock::now();
  initLeaderboard();

  m_thread = boost::thread([&t_io_service]() { t_io_service.run(); });
}

UdpServer::~UdpServer() {
  m_socket.close();
  m_io_service.stop();
}

int UdpServer::getPlayerIdCount() const { return m_player_id_count; }

void UdpServer::setPlayerIdCount(int t_new_player_id_count) {
  m_player_id_count = t_new_player_id_count;
}

void UdpServer::sendMessage(const std::string &t_msg, udp::endpoint t_client) {
  std::cout << t_msg << std::endl;
  m_socket.send_to(boost::asio::buffer(t_msg, t_msg.size()), t_client);
}

void UdpServer::handleSend(std::string t_msg,
                           const boost::system::error_code &t_error,
                           std::size_t t_size) {}

void UdpServer::receiveClient() {
  std::cout << "listening" << std::endl;
  m_socket.async_receive_from(
    boost::asio::buffer(m_recvBuffer), m_remoteEndpoint,
    boost::bind(&UdpServer::handleReceive, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
}

bool UdpServer::doesAlreadyExist(std::shared_ptr<Action> t_action) {
  if (t_action->getType() == Action::ActionType::START) {
    std::string lobby_ip = t_action->getLobbyIp();
    int id = t_action->getId();

    for (int registered_id : m_client_ports) {
      if (registered_id == id) { return true; }
    }
    m_client_ports.push_back(id);
    if (m_endpoints.size() == 0) {
      for (int i = 0; i < m_lobbys.size(); i++) {
        if (lobby_ip == m_lobbys[i].m_lobby_code) {
          for (int x = 0; x < m_lobbys[i].m_endpoints.size(); x++) {
            m_endpoints.push_back(m_lobbys[i].m_endpoints[x]);
          }
        }
      }
    }
  }
  return false;
}

bool UdpServer::checkAndLobbyHandling(std::shared_ptr<Action> t_action) {
  if (t_action->getType() == Action::ActionType::CREATELOBBY) {
    std::vector<std::string> player_names;
    player_names.push_back(t_action->getPlayerName());
    Lobby new_lobby{t_action->getLobbyIp(),
                    1,
                    player_names,
                    {m_remoteEndpoint}};
    m_lobbys.push_back(new_lobby);
    return true;
  } else if (t_action->getType() == Action::ActionType::LEAVELOBBY) {
    std::string lobby_ip = t_action->getLobbyIp();
    std::string username = t_action->getPlayerName();

    for (int i = 0; i < m_lobbys.size(); i++) {
      if (lobby_ip == m_lobbys[i].m_lobby_code) {
        for (int x = 0; x < m_lobbys[i].m_endpoints.size(); x++) {
          LeaveLobbyAction leave_lobby_action = LeaveLobbyAction(
            Action::ActionType::LEAVELOBBY, lobby_ip, username);
          sendMessage(leave_lobby_action.getCommand(),
                      m_lobbys[i].m_endpoints[x]);
          if (m_remoteEndpoint == m_lobbys[i].m_endpoints[x]) {
            m_lobbys[i].m_endpoints.erase(m_lobbys[i].m_endpoints.begin() + x);
          }
        }
        if (m_lobbys[i].m_player_count == 1 ||
            m_lobbys[i].m_player_count == 0) {
          m_lobbys.erase(m_lobbys.begin() + i);
        } else {
          m_lobbys[i].m_player_count -= 1;
          for (int x = 0; x < m_lobbys[i].m_player_names.size(); x++) {
            if (username == m_lobbys[i].m_player_names[x]) {
              m_lobbys[i].m_player_names.erase(
                m_lobbys[i].m_player_names.begin() + x);
            }
          }
        }
        break;
      }
    }
    return true;
  } else if (t_action->getType() == Action::ActionType::JOINLOBBY) {
    std::string lobby_ip = t_action->getLobbyIp();
    std::string username = t_action->getPlayerName();

    for (int i = 0; i < m_lobbys.size(); i++) {
      std::cout << m_lobbys[i].m_lobby_code << std::endl;
      if (lobby_ip == m_lobbys[i].m_lobby_code) {
        m_lobbys[i].m_player_count += 1;
        m_lobbys[i].m_player_names.push_back(username);
        m_lobbys[i].m_endpoints.push_back(m_remoteEndpoint);

        for (int x = 0; x < m_lobbys[i].m_endpoints.size(); x++) {
          JoinSuccessfullAction join_lobby_action = JoinSuccessfullAction(
            Action::ActionType::JOINSUCCESSFULL, m_lobbys[i].m_player_names);
          sendMessage(join_lobby_action.getCommand(),
                      m_lobbys[i].m_endpoints[x]);
        }
        break;
      }
    }
    return true;
  }
  return false;
}

bool UdpServer::chadHandling(std::shared_ptr<Action> t_action) {
  if (t_action->getType() == Action::ActionType::CHAD) {
    std::string msg = t_action->getChadMsg();
    std::string lobby_code = t_action->getLobbyIp();

    for (int i = 0; i < m_lobbys.size(); i++) {
      if (lobby_code == m_lobbys[i].m_lobby_code) {
        for (int x = 0; x < m_lobbys[i].m_endpoints.size(); x++) {
          ChadAction leave_lobby_action =
            ChadAction(Action::ActionType::CHAD, msg, lobby_code);
          sendMessage(leave_lobby_action.getCommand(),
                      m_lobbys[i].m_endpoints[x]);
        }
        break;
      }
    }
    return true;
  }
  return false;
}

void UdpServer::handleReceive(const boost::system::error_code &t_error,
                              std::size_t t_size) {
  if (!t_error) {
    std::string msg =
      std::string(m_recvBuffer.begin(), m_recvBuffer.begin() + t_size);
    std::cout << "Received: '" << msg << "' (" << t_error.message() << ")\n";
    m_logger.writeLog(Logger::Threatlevel::LOG,
                      "Received: '" + msg + "' (" + t_error.message() + ")");
    std::shared_ptr<Action> action = getAction(msg);
    if (checkAndLobbyHandling(action) || chadHandling(action)) {
      receiveClient();
      return;
    };
    if (!doesAlreadyExist(action)) {
      m_input_manager.addActionsToQueue(action);
      m_send_event_manager.addActionsToQueue(action);
    }

    checkIfLeaderboard(action);

    if (action->getType() != Action::ActionType::END &&
        m_client_ports.size() != 2) {
      receiveClient();
    } else if (m_client_ports.size() == m_endpoints.size()) {
      std::cout << m_endpoints.size() << std::endl;
      m_flag = GameMode::coop;
      receiveClient();
    } else {
      m_flag = GameMode::end;
      m_is_running = false;
      m_socket.close();
    }
  } else {
    m_socket.close();
  }
}

void UdpServer::addEvent(std::shared_ptr<Action> event) {
  m_send_event_manager.addActionsToQueue(event);
}

bool UdpServer::isUpdated(std::shared_ptr<Action> t_event) {
  if (t_event->getType() == Action::ActionType::START) {
    for (int id : m_client_ports) {
      if (t_event->getId() == id) { return false; }
    }
  }
  return true;
}

void UdpServer::sendEvents() {
  EventQueue eq = m_send_event_manager.getInputs();
  for (std::shared_ptr<Action> event : eq.getEventQueue()) {
    if (!isUpdated(event)) {
      std::cout << "add start event again" << std::endl;
      m_client_ids.push_back(m_client_ids.size() + 1);
      event->setClientId(m_client_ids.size());
      m_input_manager.addActionsToQueue(event);
      m_send_event_manager.addActionsToQueue(event);
      continue;
    }
    if (event->getType() == Action::ActionType::START) {
      for (int i = 0; i < m_endpoints.size(); i++) {
        if (event->getClientId() - 1 == i) {
          sendMessage(event->getCommand(), m_endpoints[i]);
        }
      }
    } else {
      for (udp::endpoint client : m_endpoints) {
        sendMessage(event->getCommand(), client);
      }
    }
  }
}

float UdpServer::getTimeDiff() {
  m_time_went_by = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = m_time_went_by - m_start_time;
  return elapsed_seconds.count();
}
void UdpServer::resetTime() {
  m_time_went_by = std::chrono::system_clock::now();
  m_start_time = std::chrono::system_clock::now();
}

void UdpServer::initLeaderboard() {
  std::vector<std::string> lines;
  std::string filename = ".leaderboard.txt";
  std::ifstream infile(filename);

  if (infile)
  {
    std::string line;
    while (std::getline(infile, line))
    {
      lines.push_back(line);
    }
    infile.close();
    m_leaderboard = lines;
  }
  else
  {
    std::ofstream outfile(filename);
    outfile.close();
    std::cout << "File created: " << filename << std::endl;
  }
}

void UdpServer::clearLeaderboard() {
  m_leaderboard.clear();
  std::string filename = ".leaderboard.txt";
  std::ofstream outfile(filename);
  outfile.close();
  std::cout << "File cleared: " << filename << std::endl;
}

bool compare_scores(const std::string& t_s1, const std::string& t_s2)
{
  size_t pos1 = t_s1.find_last_of(" ");
  size_t pos2 = t_s2.find_last_of(" ");
  int score1 = std::stoi(t_s1.substr(pos1+1));
  int score2 = std::stoi(t_s2.substr(pos2+1));
  return score1 > score2;
}

void UdpServer::updateLeaderboard(std::string t_name, int t_score) {
  int place = 1;

  bool is_in_leaderboard = false;
  for (auto element : m_leaderboard) {
    size_t pos = element.find(" ");
    if (pos != std::string::npos)
    {
      std::string name = element.substr(pos + 1);
      pos = name.find(" ");
      std::string score = name.substr(pos + 1);
      if (std::stoi(score) < t_score) {
        m_leaderboard.push_back(
          std::to_string(place) + ": " + t_name + " " + std::to_string(t_score));
        is_in_leaderboard = true;
        break;
      }
    }
    place++;
  }
  std::sort(m_leaderboard.begin(), m_leaderboard.end(), compare_scores);
  //inserted if not in leaderboard and not full
  if (!is_in_leaderboard && m_leaderboard.size() < 10) {
    m_leaderboard.push_back(
      std::to_string(place) + ": " + t_name + " " + std::to_string(t_score));
  }
  //clear leaderboard if to full
  while (m_leaderboard.size() > 10) {
    m_leaderboard.pop_back();
  }
  int correct_place = 1;
  for (auto element : m_leaderboard) {
    size_t pos = element.find(":");
    if (pos != std::string::npos) {
      int scorePlace =std::stoi(element.substr(0, pos));
      if (scorePlace != correct_place) {
        m_leaderboard[correct_place - 1] = std::to_string(correct_place) + ": " + element.substr(pos + 2);
      }
    }
    correct_place++;
  }
  std::string filename = ".leaderboard.txt";
  std::ofstream outfile(filename);
  for (auto element : m_leaderboard) {
    outfile << element << std::endl;
  }
  outfile.close();
}

void UdpServer::checkIfLeaderboard(std::shared_ptr<Action> t_action) {
  if (t_action->getType() == Action::ActionType::ASKLEADERBOARD) {
    for (udp::endpoint client : m_endpoints) {
      LeaderboardAction leaderboardAction(Action::ActionType::SENDLEADERBOARD, m_leaderboard);
      sendMessage(leaderboardAction.getCommand(), client);
    }
  }
}

std::vector<std::string> UdpServer::getLeaderboard() {return m_leaderboard;}
