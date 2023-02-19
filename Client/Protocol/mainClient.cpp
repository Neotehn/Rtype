#include <memory>
#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <chrono>
#include <thread>

#include "./UdpClient.hpp"
#include "../../Game/Encapsulation/Networking/Boost/MethodEncaps.hpp"

int main() {
  rtype::io_service io_service;
  UdpClient client(io_service, "localhost", "50000", 51000);

  while (1) {
    client.sendMessage("hola hombre");
    rtype::thread_sleep(1000);
  }
  return 0;
}
