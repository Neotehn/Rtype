#include <memory>
#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <chrono>
#include <thread>

#include "./UdpClient.hpp"

int main() {
  boost::asio::io_service io_service;
  UdpClient client(io_service, "localhost", "50000", 51000);

  while (1) {
    client.sendMessage("hola hombre");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
  return 0;
}
