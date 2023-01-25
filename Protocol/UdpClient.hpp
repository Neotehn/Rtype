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
  UdpClient(boost::asio::io_service &t_io_service,
            const std::string &t_host,
            const std::string &t_port);
  ~UdpClient();
  void sendMessage(const std::string &);

 private:
  udp::socket m_socket;
  udp::endpoint m_remoteEndpoint;
  std::array<char, 1024> m_recvBuffer;
  boost::asio::io_service &m_io_service;
};

#endif /* !PROTOCOL_UDPCLIENT_HPP_ */
