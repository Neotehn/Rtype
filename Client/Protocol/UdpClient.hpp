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
#include "../../Protocol/BinarySerialization.hpp"

using boost::asio::ip::udp;

class UdpClient : public IProtocol {
 public:
  UdpClient(boost::asio::io_service &t_io_service, const std::string &t_host,
            const std::string &t_port, const std::size_t &t_ownPort,
            InputManager &t_input_manager,
            InputManager &t_client_input_manager);
  ~UdpClient();
  void sendMessage(const std::string &);
  void receiveClient();
  void handleReceive(const boost::system::error_code &error, std::size_t size);
  void handleSend(std::string t_msg, const boost::system::error_code &t_error,
                  std::size_t t_size);
  enum ConnectState { none, connected };
  ConnectState m_flag;

 private:
  udp::socket m_socket;
  udp::endpoint m_remoteEndpoint;
  std::array<char, 1024> m_recvBuffer;
  boost::asio::io_service &m_io_service;
  InputManager &m_input_manager;
  InputManager &m_client_input_manager;
  boost::thread m_thread;
  BinarySerialization m_received_data;
};

#endif /* !PROTOCOL_UDPCLIENT_HPP_ */
