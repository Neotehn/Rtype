#include "./UdpClient.hpp"

UdpClient::UdpClient(boost::asio::io_service &t_io_service,
                     const std::string &t_host, const std::string &t_port)
    : m_io_service(t_io_service), m_socket(t_io_service),
      m_remoteEndpoint(udp::v4(), stoi(t_port)) {
  m_socket.open(udp::v4());
  m_socket.set_option(boost::asio::socket_base::broadcast(true));
}

UdpClient::~UdpClient() { m_socket.close(); }

void UdpClient::sendMessage(const std::string &t_msg) {
  m_socket.send_to(boost::asio::buffer(t_msg, t_msg.size()), m_remoteEndpoint);
}
