#ifndef PROTOCOL_UDPSERVER_HPP_
#define PROTOCOL_UDPSERVER_HPP_

#include <memory>
#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "./IProtocol.hpp"

using boost::asio::ip::udp;

class UdpServer : public IProtocol {
 public:
  UdpServer(boost::asio::io_service &);
  ~UdpServer();

 private:
  void startListening();
  void handleListening(const boost::system::error_code &error,
                       std::size_t bytes_transferred);
  void handleSend(std::shared_ptr<std::string> msg,
                  const boost::system::error_code &ec,
                  std::size_t bytes_transferred);

  udp::socket _socket;
  udp::endpoint _endpoint;
  std::array<char, 1024> _recvBuffer;
};

#endif /* !PROTOCOL_UDPSERVER_HPP_ */
