#include <memory>
#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "./UdpServer.hpp"
#include "../Encapsulation/Networking/Boost/MethodEncaps.hpp"

int main() {
  try {
    rtype::IIoService io_service;
    UdpServer server(io_service);
    boost::thread thread([&io_service]() { io_service.run(); });
    std::cout << "yes" << std::endl;
    while (1) {
      if (server.m_flag) { server.sendMessage("hola chica"); }
      rtype::thread_sleep(1000);
    }
  } catch (const std::exception &er) { std::cerr << er.what() << std::endl; }
  return 0;
}
