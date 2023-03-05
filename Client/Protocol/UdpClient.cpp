#include "./UdpClient.hpp"

UdpClient::UdpClient(boost::asio::io_service &t_io_service,
                     const std::string &t_host, const std::string &t_port,
                     const std::size_t &t_ownPort)
    : m_io_service(t_io_service),
      m_remoteEndpoint(boost::asio::ip::address::from_string(t_host),
                       stoi(t_port)),
      m_socket(t_io_service, udp::endpoint(udp::v4(), t_ownPort)) {
  m_flag = ConnectState::none;
  m_id = 0;
  m_port_number = t_ownPort;
  m_lobby_successfull_connected = false;
  receiveClient();
  m_thread = boost::thread([&t_io_service]() { t_io_service.run(); });
  m_player_name = "";
}

UdpClient::~UdpClient() {
  m_io_service.stop();
  m_socket.close();
}

void UdpClient::sendMessage(const std::string &t_msg) {
  m_socket.send_to(boost::asio::buffer(t_msg, t_msg.size()), m_remoteEndpoint);
}

void UdpClient::handleSend(std::string t_msg,
                           const boost::system::error_code &t_error,
                           std::size_t t_size) {}

void UdpClient::receiveClient() {
  std::cout << "listening" << std::endl;
  m_socket.async_receive_from(
    boost::asio::buffer(m_recvBuffer), m_remoteEndpoint,
    boost::bind(&UdpClient::handleReceive, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
}

void UdpClient::setPlayerId(std::shared_ptr<Action> t_action) {
  if (!m_client_input_manager->isPlayerIdSet()) {
    if (t_action->getType() == Action::ActionType::START) {
      m_client_input_manager->setPlayerId(t_action->getId());
      m_id = t_action->getClientId();
      std::cout << "id: " << std::to_string(t_action->getClientId())
                << std::endl;
    }
  }
}

bool UdpClient::checkAndHandleLobbyJoining(std::shared_ptr<Action> t_action) {
  if (t_action->getType() == Action::ActionType::JOINSUCCESSFULL) {
    m_lobby_successfull_connected = true;
    m_lobby_names = t_action->getLobbyPlayerNames();
    return true;
  } else if (t_action->getType() == Action::ActionType::LEAVELOBBY) {
    for (int i = 0; i < m_lobby_names.size(); i++) {
      if (m_lobby_names[i] == t_action->getPlayerName()) {
        m_lobby_names.erase(m_lobby_names.begin() + i);
        break;
      }
    }
    std::cout << std::to_string(m_lobby_names.size()) << std::endl;
    return true;
  }
  return false;
}

bool UdpClient::chadHandling(std::shared_ptr<Action> t_action) {
  if (t_action->getType() == Action::ActionType::CHAD) {
    std::string msg = t_action->getChadMsg();

    m_chad_msgs.push_back(msg);
    if (m_chad_msgs.size() == 10) {
      for (int i = 0; i < 10; i++) {
        m_chad_msgs.pop_back();
      }
      m_chad_msgs.push_back(msg);
    }
    return true;
  }
  return false;
}

void UdpClient::handleReceive(const boost::system::error_code &t_error,
                              std::size_t t_size) {
  if (!t_error) {
    std::string msg =
      std::string(m_recvBuffer.begin(), m_recvBuffer.begin() + t_size);
    try {
      std::shared_ptr<Action> action = getAction(msg);
      if (checkAndHandleLobbyJoining(action) || chadHandling(action)) {
        receiveClient();
        return;
      }
      setPlayerId(action);
      //      if (!m_client_input_manager.doesActionExist(action)) {
      m_client_input_manager->addActionsToQueue(action);
      checkIfLeaderboard(action);
      //      }
    } catch (std::exception &e) {
      std::cout << "Error: " << e.what() << std::endl;
    }
    EventQueue eq = m_client_input_manager->getInputs();
    for (std::shared_ptr<Action> action : eq.getEventQueue()) {
      m_input_manager->addActionsToQueue(action);
    }

    std::cout << "Received: '" << msg << "' (" << t_error.message() << ")\n";
    m_flag = ConnectState::connected;
    if (std::string(m_recvBuffer.begin(), m_recvBuffer.begin() + t_size) !=
        "END\n") {
      receiveClient();
    }
  } else {
    m_socket.close();
  }
}

std::size_t UdpClient::getPortNumber() const { return m_port_number; }

void UdpClient::setInputManager(InputManager *t_input_manager) {
  m_input_manager = t_input_manager;
}

void UdpClient::setClientInputManager(InputManager *t_client_input_manager) {
  m_client_input_manager = t_client_input_manager;
}

std::string UdpClient::getPlayerName() { return m_player_name; }

void UdpClient::setPlayerName(std::string t_new_name) {
  m_player_name = t_new_name;
}

void UdpClient::setLeaderboard(std::vector<std::string> t_leaderboard) {
  m_leaderboard = t_leaderboard;
}

std::vector<std::string> UdpClient::getLeaderboard() { return m_leaderboard; }

void UdpClient::checkIfLeaderboard(std::shared_ptr<Action> t_action) {
  if (t_action->getType() == Action::ActionType::SENDLEADERBOARD) {
    setLeaderboard(t_action->getLeaderboard());
    std::cout << "leaderboard: " << std::endl;
    for (auto &i : m_leaderboard) {
      std::cout << i << std::endl;
    }
  }
}

void UdpClient::clearData() {
  m_id = 0;
  m_lobby_code = "";
  m_lobby_names.clear();
  m_chad_msgs.clear();
  m_input_manager = nullptr;
  m_client_input_manager = nullptr;
  m_flag = ConnectState::none;
}