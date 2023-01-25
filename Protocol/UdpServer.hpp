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

#include "./IProtocol.hpp"
#include "./UdpSession.hpp"

using boost::asio::ip::udp;
using boost::system::error_code;

class UdpServer : public IProtocol {
  typedef boost::shared_ptr<UdpSession> shared_session;
 public:
  UdpServer(boost::asio::io_service &);
  ~UdpServer();

 private:
  void startListening();
  void handleListening(shared_session t_session,
                       const error_code& t_ec,
                       std::size_t);
  void handleSend(std::shared_ptr<std::string> t_msg,
                  const boost::system::error_code &t_ec,
                  std::size_t t_bytes_transferred);
  void handle(shared_session t_session,
                      const error_code &t_ec,
                      std::size_t);
  void enqueueResponse(shared_session const& t_session);
  void enqueueResponseStrand(shared_session const& t_session);

  udp::socket m_socket;
  boost::asio::io_context::strand m_strand;

  friend struct UdpSession;
};

#endif /* !PROTOCOL_UDPSERVER_HPP_ */
