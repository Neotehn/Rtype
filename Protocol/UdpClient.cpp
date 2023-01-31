#include "./UdpClient.hpp"

UdpClient::UdpClient(boost::asio::io_service &t_io_service,
                     const std::string &t_host, const std::string &t_port)
    : m_io_service(t_io_service), m_remoteEndpoint(udp::v4(), stoi(t_port)),
      m_socket(t_io_service, udp::endpoint(udp::v4(), 28000)) {
  sendMessage("First Message");
  receiveClient();
  t_io_service.run();
}

UdpClient::~UdpClient() { m_socket.close(); }

void UdpClient::sendMessage(const std::string &t_msg) {
  m_socket.send_to(boost::asio::buffer(t_msg, t_msg.size()), m_remoteEndpoint);
}

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
    std::cout << "Received: '"
              << std::string(m_recvBuffer.begin(),
                             m_recvBuffer.begin() + t_size)
              << "' (" << t_error.message() << ")\n";
    if (std::string(m_recvBuffer.begin(), m_recvBuffer.begin() + t_size) !=
        "END\n") {
      sendMessage("One More Time");
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      receiveClient();
    }
  } else {
    m_socket.close();
  }
}