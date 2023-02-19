#ifndef PROTOCOL_UDPCLIENT_HPP_
#define PROTOCOL_UDPCLIENT_HPP_

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include "../../Protocol/IProtocol.hpp"
#include "../src/InputManager/InputManager.hpp"

#include "../../Game/Encapsulation/Networking/NetworkDataTypes.hpp"
#include "../../Game/Encapsulation/Networking/IIoService.hpp"
#include "../../Game/Encapsulation/Networking/Boost/IoService.hpp"
#include "../../Game/Encapsulation/Networking/Boost/ErrorCode.hpp"
#include "../../Game/Encapsulation/Networking/Boost/MethodEncaps.hpp"

using boost::asio::ip::udp;

class UdpClient : public IProtocol {
 public:
  UdpClient(rtype::IIoService &t_io_service, const std::string &t_host,
            const std::string &t_port, const std::size_t &t_ownPort,
            InputManager &t_input_manager,
            InputManager &t_client_input_manager);
  ~UdpClient();
  void sendMessage(const std::string &);
  void receiveClient();
  void handleReceive(const rtype::ErrorCode &error, std::size_t size);
  void handleSend(std::string t_msg, const rtype::ErrorCode &t_error,
                  std::size_t t_size);
  enum ConnectState { none, connected };
  ConnectState m_flag;

 private:
  udp::socket m_socket;
  udp::endpoint m_remoteEndpoint;
  std::array<char, 1024> m_recvBuffer;
  rtype::IIoService &m_io_service;
  InputManager &m_input_manager;
  InputManager &m_client_input_manager;
  boost::thread m_thread;
};

#endif /* !PROTOCOL_UDPCLIENT_HPP_ */
