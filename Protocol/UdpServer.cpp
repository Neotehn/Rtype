#include "./UdpServer.hpp"

using boost::asio::ip::udp;

UdpServer::UdpServer(boost::asio::io_service &io_service) :
_socket(io_service, udp::endpoint(udp::v4(), 27000)) {
  startListening();
}

UdpServer::~UdpServer() {
  _socket.close();
}

void UdpServer::startListening() {
  _socket.async_receive_from(boost::asio::buffer(_recvBuffer),
                    _endpoint,
                    boost::bind(&UdpServer::handleListening,
                                this,
                                boost::asio::placeholders::error,
                                boost::asio::placeholders::bytes_transferred));
}

void UdpServer::handleSend(std::shared_ptr<std::string> msg,
                           const boost::system::error_code &ec,
                           std::size_t bytes_transferred) {
  startListening();
}

void UdpServer::handleListening(const boost::system::error_code &error,
                                std::size_t bytes_transferred) {
  if (!error || error == boost::asio::error::message_size) {
    std::cout << "Received: '" << std::string(_recvBuffer.begin(),
    _recvBuffer.begin() + bytes_transferred) << "' (" <<
    error.message() << ")\n";

    auto message = std::make_shared<std::string>("Hello\n");

    _socket.async_send_to(boost::asio::buffer(*message),
              _endpoint,
              boost::bind(&UdpServer::handleSend,
                          this,
                          message,
                          boost::asio::placeholders::error,
                          boost::asio::placeholders::bytes_transferred));
  }
}
