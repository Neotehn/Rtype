# Server

The server is multi-threaded and implements the game logic. The server waits for the client to connect and if the connection is established  and both clients pressed start the server will send all updates to the client. For example the server would receive input and responds with the new position or if the client shoots a bullet the server will create a bullet send it to the client and inform the client if the enemy was hit.

To communicate with the client the server runs our UDPServer protocol.

UDPServer.hpp:

```
#ifndef PROTOCOL_UDPSERVER_HPP_
#define PROTOCOL_UDPSERVER_HPP_

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
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
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <math.h>

#include "../../Protocol/IProtocol.hpp"
#include "../../Client/src/InputManager/InputManager.hpp"
#include "./UdpSession.hpp"
#include "../src/Logger.hpp"

using boost::asio::ip::udp;
using boost::system::error_code;

class UdpServer : public IProtocol {
 public:
  UdpServer(boost::asio::io_service &t_io_service,
            InputManager &t_input_manager, bool &t_is_running,
            std::string t_ip);
  ~UdpServer();
  void sendMessage(const std::string &, udp::endpoint t_client);
  void receiveClient();
  void handleReceive(const boost::system::error_code &error, std::size_t size);
  void handleSend(std::string t_msg, const boost::system::error_code &t_error,
                  std::size_t t_size);

  void addEvent(std::shared_ptr<Action> event);
  void sendEvents();
  int getPlayerIdCount() const;
  void setPlayerIdCount(int t_new_player_id_count);
  bool checkAndLobbyHandling(std::shared_ptr<Action> t_action);

  float getTimeDiff();
  void resetTime();

  enum GameMode { none, single, coop, end };
  GameMode m_flag;
  std::vector<int> m_client_ids;

 private:
  std::vector<int> m_client_ports;
  std::vector<udp::endpoint> m_endpoints;
  std::vector<Lobby> m_lobbys;
  boost::thread m_thread;
  udp::socket m_socket;
  udp::endpoint m_remoteEndpoint;
  std::array<char, 1024> m_recvBuffer;
  boost::asio::io_service &m_io_service;
  InputManager &m_input_manager;
  InputManager m_send_event_manager;
  Logger m_logger;
  bool &m_is_running;
  int m_player_id_count;
  std::chrono::system_clock::time_point m_start_time;
  std::chrono::system_clock::time_point m_time_went_by;

  bool doesAlreadyExist(std::shared_ptr<Action> t_action);
  bool isUpdated(std::shared_ptr<Action> t_event);
};
```

UDPServer.cpp:

```
#ifndef PROTOCOL_UDPSERVER_HPP_
#define PROTOCOL_UDPSERVER_HPP_

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
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
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <math.h>

#include "../../Protocol/IProtocol.hpp"
#include "../../Client/src/InputManager/InputManager.hpp"
#include "./UdpSession.hpp"
#include "../src/Logger.hpp"

using boost::asio::ip::udp;
using boost::system::error_code;

class UdpServer : public IProtocol {
 public:
  UdpServer(boost::asio::io_service &t_io_service,
            InputManager &t_input_manager, bool &t_is_running,
            std::string t_ip);
  ~UdpServer();
  void sendMessage(const std::string &, udp::endpoint t_client);
  void receiveClient();
  void handleReceive(const boost::system::error_code &error, std::size_t size);
  void handleSend(std::string t_msg, const boost::system::error_code &t_error,
                  std::size_t t_size);

  void addEvent(std::shared_ptr<Action> event);
  void sendEvents();
  int getPlayerIdCount() const;
  void setPlayerIdCount(int t_new_player_id_count);
  bool checkAndLobbyHandling(std::shared_ptr<Action> t_action);

  float getTimeDiff();
  void resetTime();

  enum GameMode { none, single, coop, end };
  GameMode m_flag;
  std::vector<int> m_client_ids;

 private:
  std::vector<int> m_client_ports;
  std::vector<udp::endpoint> m_endpoints;
  std::vector<Lobby> m_lobbys;
  boost::thread m_thread;
  udp::socket m_socket;
  udp::endpoint m_remoteEndpoint;
  std::array<char, 1024> m_recvBuffer;
  boost::asio::io_service &m_io_service;
  InputManager &m_input_manager;
  InputManager m_send_event_manager;
  Logger m_logger;
  bool &m_is_running;
  int m_player_id_count;
  std::chrono::system_clock::time_point m_start_time;
  std::chrono::system_clock::time_point m_time_went_by;

  bool doesAlreadyExist(std::shared_ptr<Action> t_action);
  bool isUpdated(std::shared_ptr<Action> t_event);
};

#endif /* !PROTOCOL_UDPSERVER_HPP_ */
```

[Back](../../README.md)
