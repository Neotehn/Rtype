#include "./UdpServer.hpp"

using boost::asio::ip::udp;

UdpServer::UdpServer(boost::asio::io_service &t_io_service) :
                     m_socket(t_io_service, udp::endpoint(udp::v4(), 27000)) {
  std::cout << "hello folk" << std::endl;
  startListening();
}

UdpServer::~UdpServer() {
  m_socket.close();
}

void UdpServer::startListening() {
  m_socket.async_receive_from(boost::asio::buffer(m_recvBuffer),
                    m_endpoint,
                    boost::bind(&UdpServer::handleListening,
                                this,
                                boost::asio::placeholders::error,
                                boost::asio::placeholders::bytes_transferred));
}

void UdpServer::handleSend(std::shared_ptr<std::string> t_msg,
                           const boost::system::error_code &t_ec,
                           std::size_t t_bytes_transferred) {
  startListening();
}

void UdpServer::handleListening(const boost::system::error_code &t_error,
                                std::size_t t_bytes_transferred) {
  if (!t_error || t_error == boost::asio::error::message_size) {
    std::cout << "Received: '" << std::string(m_recvBuffer.begin(),
    m_recvBuffer.begin() + t_bytes_transferred) << "' (" <<
    t_error.message() << ")\n";

    auto message = std::make_shared<std::string>("Hello\n");

    m_socket.async_send_to(boost::asio::buffer(*message),
              m_endpoint,
              boost::bind(&UdpServer::handleSend,
                          this,
                          message,
                          boost::asio::placeholders::error,
                          boost::asio::placeholders::bytes_transferred));
  }
}
