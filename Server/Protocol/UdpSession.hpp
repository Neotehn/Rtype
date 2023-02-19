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

#include "../../Game/Encapsulation/Networking/NetworkDataTypes.hpp"
#include "../../Game/Encapsulation/Networking/Boost/ErrorCode.hpp"

using boost::asio::ip::udp;

class UdpServer;

class UdpSession : public boost::enable_shared_from_this<UdpSession> {
 public:
  UdpSession(UdpServer *t_server);
  void handleRequest(const rtype::ErrorCode &t_error, std::size_t);
  void handleSent(const rtype::ErrorCode &t_ec, std::size_t);

  udp::endpoint m_remoteEndpoint;
  std::array<char, 1024> m_recvBuffer;
  std::string m_message;
  UdpServer *m_server;
};

#endif /* !PROTOCOL_UDPSESSION_HPP_ */
