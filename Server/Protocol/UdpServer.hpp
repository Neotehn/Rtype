#ifndef PROTOCOL_UDPSERVER_HPP_
#define PROTOCOL_UDPSERVER_HPP_

#include <memory>
#include <string>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "../../Protocol/IProtocol.hpp"
#include "./UdpSession.hpp"

using boost::asio::ip::udp;
using boost::system::error_code;

class UdpServer : public IProtocol {
 public:
  UdpServer(boost::asio::io_service &t_io_service);
  ~UdpServer();
  void sendMessage(const std::string &);
  void receiveClient();
  void handleReceive(const boost::system::error_code &error, std::size_t size);
  void handleSend(std::string t_msg, const boost::system::error_code &t_error,
                  std::size_t t_size);

  std::size_t m_flag;

 private:
  udp::socket m_socket;
  udp::endpoint m_remoteEndpoint;
  std::array<char, 1024> m_recvBuffer;
  boost::asio::io_service &m_io_service;
};

#endif /* !PROTOCOL_UDPSERVER_HPP_ */
