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

using boost::asio::ip::udp;

class UdpClient : public IProtocol {
 public:
  UdpClient(boost::asio::io_service &t_io_service, const std::string &t_host,
            const std::string &t_port, const std::size_t &t_ownPort);
  ~UdpClient();
  void sendMessage(const std::string &);
  void receiveClient();
  void handleReceive(const boost::system::error_code &error, std::size_t size);
  void handleSend(std::string t_msg, const boost::system::error_code &t_error,
                  std::size_t t_size);
  std::size_t getPortNumber() const;
  void setInputManager(InputManager *t_input_manager);
  void setClientInputManager(InputManager *t_client_input_manager);
  bool checkAndHandleLobbyJoining(std::shared_ptr<Action> t_action);
  enum ConnectState { none, connected };
  std::string getPlayerName();
  void setPlayerName(std::string t_new_name);
  ConnectState m_flag;
  int m_id;
  std::string m_lobby_code;
  std::vector<std::string> m_lobby_names;
  bool m_lobby_successfull_connected;

 private:
  udp::socket m_socket;
  udp::endpoint m_remoteEndpoint;
  std::array<char, 1024> m_recvBuffer;
  boost::asio::io_service &m_io_service;
  InputManager *m_input_manager = nullptr;
  InputManager *m_client_input_manager = nullptr;
  boost::thread m_thread;
  std::size_t m_port_number;
  std::string m_player_name;

  void setPlayerId(std::shared_ptr<Action> t_action);
};

#endif /* !PROTOCOL_UDPCLIENT_HPP_ */
