#include <memory>
#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "./UdpClient.hpp"

int main() {
  boost::asio::io_service io_service;
  UdpClient client(io_service, "localhost", "27000");

  client.sendMessage("Hello, World!\n");
  return 0;
}
