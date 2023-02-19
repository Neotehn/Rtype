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
#include "../../Client/src/InputManager/InputManager.hpp"
#include "./UdpSession.hpp"

#include "../../Game/Encapsulation/Networking/NetworkDataTypes.hpp"
#include "../../Game/Encapsulation/Networking/IIoService.hpp"
#include "../../Game/Encapsulation/Networking/Boost/IoService.hpp"
#include "../../Game/Encapsulation/Networking/Boost/ErrorCode.hpp"
#include "../../Game/Encapsulation/Networking/Boost/MethodEncaps.hpp"

using boost::asio::ip::udp;

class UdpServer : public IProtocol {
 public:
  UdpServer(rtype::IIoService &t_io_service, InputManager &t_input_manager,
            bool &t_is_running);
  ~UdpServer();
  void sendMessage(const std::string &);
  void receiveClient();
  void handleReceive(const rtype::ErrorCode &error, std::size_t size);
  void handleSend(std::string t_msg, const rtype::ErrorCode &t_errort_error,
                  std::size_t t_size);

  void addEvent(std::shared_ptr<Action> event);
  void sendEvents();

  enum GameMode { none, single, coop, end };
  GameMode m_flag;

 private:
  boost::thread m_thread;
  udp::socket m_socket;
  udp::endpoint m_remoteEndpoint;
  std::array<char, 1024> m_recvBuffer;
  rtype::IIoService &m_io_service;
  std::array<int, 2> remotePortArray;
  InputManager &m_input_manager;
  InputManager m_send_event_manager;
  bool &m_is_running;
};

#endif /* !PROTOCOL_UDPSERVER_HPP_ */
