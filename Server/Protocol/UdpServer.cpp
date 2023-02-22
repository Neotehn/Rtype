#include "./UdpServer.hpp"

UdpServer::UdpServer(boost::asio::io_service &t_io_service,
                     InputManager &t_input_manager, bool &t_is_running)
    : m_io_service(t_io_service), m_input_manager(t_input_manager),
      m_socket(t_io_service, udp::endpoint(udp::v4(), 50000)),
      m_is_running(t_is_running) {
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
  std::cout << "listening" << std::endl;
  m_socket.async_receive_from(
    boost::asio::buffer(m_recvBuffer), m_remoteEndpoint,
    boost::bind(&UdpServer::handleReceive, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
}

bool UdpServer::doesAlreadyExist(std::shared_ptr<Action> t_action) {
  if (t_action->getType() == Action::ActionType::START) {
    int id = t_action->getId();

    for (int registered_id : m_client_ports) {
      if (registered_id == id) { return true; }
    }
    std::cout << "register new client port: " << std::to_string(id)
              << std::endl;
    m_client_ports.push_back(id);
  }
  return false;
}

void UdpServer::handleReceive(const boost::system::error_code &t_error,
                              std::size_t t_size) {
  if (!t_error) {
    std::string msg =
      std::string(m_recvBuffer.begin(), m_recvBuffer.begin() + t_size);
    std::cout << "Received: '" << msg << "' (" << t_error.message() << ")\n";
    std::shared_ptr<Action> action = getAction(msg);
    if (!doesAlreadyExist(action)) {
      m_input_manager.addActionsToQueue(action);
      m_send_event_manager.addActionsToQueue(action);
    }

    if (action->getType() != Action::ActionType::END) {
      m_flag = GameMode::single;
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
      m_input_manager.addActionsToQueue(event);
      m_send_event_manager.addActionsToQueue(event);
      continue;
    }
    if (event->getType() != Action::ActionType::SHOOT &&
        event->getType() != Action::ActionType::UP &&
        event->getType() != Action::ActionType::DOWN &&
        event->getType() != Action::ActionType::LEFT &&
        event->getType() != Action::ActionType::RIGHT) {
      sendMessage(event->getCommand());
    }
  }
}
