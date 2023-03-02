#ifndef PROTOCOL_UDPSESSION_HPP_
#define PROTOCOL_UDPSESSION_HPP_

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

using boost::asio::ip::udp;
using boost::system::error_code;

class UdpServer;

class UdpSession : public boost::enable_shared_from_this<UdpSession> {
 public:
  UdpSession(UdpServer *t_server);
  void handleSent(const error_code &t_ec, std::size_t);

  udp::endpoint m_remoteEndpoint;
  boost::array<char, 100> m_recvBuffer;
  std::string m_message;
  UdpServer *m_server;
};

#endif /* !PROTOCOL_UDPSESSION_HPP_ */
