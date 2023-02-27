#include "./UdpClient.hpp"

UdpClient::UdpClient(boost::asio::io_service &t_io_service,
                     const std::string &t_host, const std::string &t_port,
                     const std::size_t &t_ownPort,
                     InputManager &t_input_manager,
                     InputManager &t_client_input_manager)
    : m_io_service(t_io_service), m_remoteEndpoint(udp::v4(), stoi(t_port)),
      m_socket(t_io_service, udp::endpoint(udp::v4(), t_ownPort)),
      m_input_manager(t_input_manager),
      m_client_input_manager(t_client_input_manager) {
  m_flag = ConnectState::none;
  m_id = 0;
  receiveClient();
  m_thread = boost::thread([&t_io_service]() { t_io_service.run(); });
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
  if (!m_client_input_manager.isPlayerIdSet()) {
    if (t_action->getType() == Action::ActionType::CONNECT) {
      m_client_input_manager.setPlayerId(t_action->getId());
      m_id = t_action->getClientId();
      std::cout << "id: " << std::to_string(t_action->getClientId())
                << std::endl;
    }
  }
}

void UdpClient::handleReceive(const boost::system::error_code &t_error,
                              std::size_t t_size) {
  if (!t_error) {
    std::string msg =
      std::string(m_recvBuffer.begin(), m_recvBuffer.begin() + t_size);
    try {
      std::shared_ptr<Action> action = getAction(msg);
      setPlayerId(action);
      //      if (!m_client_input_manager.doesActionExist(action)) {
      m_client_input_manager.addActionsToQueue(action);
      //      }
    } catch (std::exception &e) {
      std::cout << "Error: " << e.what() << std::endl;
    }

    EventQueue eq = m_client_input_manager.getInputs();
    for (std::shared_ptr<Action> action : eq.getEventQueue()) {
      m_input_manager.addActionsToQueue(action);
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