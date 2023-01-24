#ifndef PROTOCOL_UDPCLIENT_HPP_
#define PROTOCOL_UDPCLIENT_HPP_

#include <memory>
#include <string>
#include <iostream>
#include <sstream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "./IProtocol.hpp"

using boost::asio::ip::udp;

class UdpClient : public IProtocol {
 public:
  UdpClient(boost::asio::io_service &io_service,
            const std::string &host,
            const std::string &port);
  ~UdpClient();
  void sendMessage(const std::string &);

 private:
  udp::socket _socket;
  udp::endpoint _remoteEndpoint;
  std::array<char, 1024> _recvBuffer;
  boost::asio::io_service &_io_service;
};

#endif /* !PROTOCOL_UDPCLIENT_HPP_ */
