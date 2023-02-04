#include "./UdpClient.hpp"

UdpClient::UdpClient(boost::asio::io_service &t_io_service,
                     const std::string &t_host, const std::string &t_port,
                     const std::size_t &t_ownPort,
                     InputManager &t_input_manager)
    : m_io_service(t_io_service), m_remoteEndpoint(udp::v4(), stoi(t_port)),
      m_socket(t_io_service, udp::endpoint(udp::v4(), t_ownPort)),
      m_input_manager(t_input_manager) {
  m_io_service.poll();
  m_io_service.reset();
  m_flag = ConnectState::none;
  receiveClient();
}

UdpClient::~UdpClient() {
  m_io_service.stop();
  m_socket.close();
}

void UdpClient::sendMessage(const std::string &t_msg) {
  m_socket.send_to(boost::asio::buffer(t_msg, t_msg.size()), m_remoteEndpoint);
  m_io_service.poll();
  m_io_service.reset();
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

void UdpClient::handleReceive(const boost::system::error_code &t_error,
                              std::size_t t_size) {
  if (!t_error) {
    std::string msg =
      std::string(m_recvBuffer.begin(), m_recvBuffer.begin() + t_size);
    IAction action = getAction(msg);
    m_input_manager.addActionsToQueue(action);

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