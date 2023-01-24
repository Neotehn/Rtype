#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <memory>
#include <string>
#include <iostream>

#include "Protocol/UdpServer.hpp"

int main()
{
  try
  {
    boost::asio::io_service io_service;
    UdpServer server(io_service);
    io_service.run();
  } catch (const std::exception& er)
  {
    std::cerr << er.what() << std::endl;
  }
  return 0;
}
