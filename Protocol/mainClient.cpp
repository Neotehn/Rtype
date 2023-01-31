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
  UdpClient client(io_service, "localhost", "27000");
  return 0;
}
