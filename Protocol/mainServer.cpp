#include <memory>
#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "./UdpServer.hpp"

int main() {
  try {
    boost::asio::io_service io_service;

    UdpServer server(io_service);
    boost::thread_group group;
    for (unsigned i = 0; i < boost::thread::hardware_concurrency(); ++i) {
      group.create_thread(
        bind(&boost::asio::io_service::run, boost::ref(io_service))
        );
    }
    group.join_all();
  } catch (const std::exception &er) {
    std::cerr << er.what() << std::endl;
  }
  return 0;
}
