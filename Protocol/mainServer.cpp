#include <memory>
#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "./UdpServer.hpp"

int main() {
  try {
    std::vector<std::thread> threads;
    auto count = std::thread::hardware_concurrency() * 2;
    boost::asio::io_service io_service;

    UdpServer server(io_service);
    for (int n = 0; n < count; ++n) {
      std::cout << "yes" << std::endl;
      threads.emplace_back([&]{io_service.run();});
    }

    for (auto &thread : threads) {
      if (thread.joinable()) {
        thread.join();
      }
    }
  } catch (const std::exception &er) {
    std::cerr << er.what() << std::endl;
  }
  return 0;
}
