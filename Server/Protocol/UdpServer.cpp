#include "./UdpServer.hpp"

UdpServer::UdpServer(boost::asio::io_service &t_io_service,
                     InputManager &t_input_manager)
    : m_io_service(t_io_service), m_input_manager(t_input_manager),
      m_socket(t_io_service, udp::endpoint(udp::v4(), 50000)) {
  m_flag = GameMode::none;
  receiveClient();

  m_thread = boost::thread([&t_io_service]() { t_io_service.run(); });
}

UdpServer::~UdpServer() {
  m_socket.close();
  m_io_service.stop();
}

void UdpServer::sendMessage(const std::string &t_msg) {
  std::cout << t_msg << std::endl;
  m_socket.send_to(boost::asio::buffer(t_msg, t_msg.size()), m_remoteEndpoint);
}

void UdpServer::handleSend(std::string t_msg,
                           const boost::system::error_code &t_error,
                           std::size_t t_size) {}

void UdpServer::receiveClient() {
  std::cout << "listening to port " << m_remoteEndpoint.port() << std::endl;
  m_socket.async_receive_from(
    boost::asio::buffer(m_recvBuffer), m_remoteEndpoint,
    boost::bind(&UdpServer::handleReceive, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
}

void UdpServer::handleReceive(const boost::system::error_code &t_error,
                              std::size_t t_size) {
  if (!t_error) {
    std::string msg =
      std::string(m_recvBuffer.begin(), m_recvBuffer.begin() + t_size);
    std::cout << "Received: '" << msg << "' (" << t_error.message() << ")\n";
    std::shared_ptr<Action> action = getAction(msg);
    m_input_manager.addActionsToQueue(action);
    m_send_event_manager.addActionsToQueue(action);

    if (std::string(m_recvBuffer.begin(), m_recvBuffer.begin() + t_size) !=
        "END\n") {
      if (m_flag == GameMode::none) {
        m_flag = GameMode::single;
        //m_remotePortArray[0] = m_remoteEndpoint.port();
        std::cout << "ertser connected" << std::endl;
        receiveClient();
      } else {
        if (m_remotePortArray[0] == m_remoteEndpoint.port() or m_flag == GameMode::none) // not sure if none check is nessessary
          return;
        //m_remotePortArray[1] = m_remoteEndpoint.port();
        std::cout << "zweiter connected" << std::endl;
        m_flag = GameMode::coop;
        receiveClient();
      }
    }
  } else {
    m_socket.close();
  }
}

void UdpServer::addEvent(std::shared_ptr<Action> event) {
  m_send_event_manager.addActionsToQueue(event);
}

void UdpServer::sendEvents() {
  EventQueue eq = m_send_event_manager.getInputs();
  for (std::shared_ptr<Action> event : eq.getEventQueue()) {
    if (event->getType() != Action::ActionType::SHOOT &&
        event->getType() != Action::ActionType::UP &&
        event->getType() != Action::ActionType::DOWN &&
        event->getType() != Action::ActionType::LEFT &&
        event->getType() != Action::ActionType::RIGHT) {
      sendMessage(event->getCommand());
    }
  }
}
