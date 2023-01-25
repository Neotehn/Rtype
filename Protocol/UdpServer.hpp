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
  void handleListening(const boost::system::error_code &t_error,
                       std::size_t t_bytes_transferred);
  void handleSend(std::shared_ptr<std::string> t_msg,
                  const boost::system::error_code &t_ec,
                  std::size_t t_bytes_transferred);

  udp::socket m_socket;
  udp::endpoint m_endpoint;
  std::array<char, 1024> m_recvBuffer;
};

#endif /* !PROTOCOL_UDPSERVER_HPP_ */
