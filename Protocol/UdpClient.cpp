#include "UdpClient.hpp"

UdpClient::UdpClient(boost::asio::io_service& io_service, const std::string& host, const std::string& port) : _io_service(io_service), _socket(io_service), _remoteEndpoint(udp::v4(), stoi(port))
{
    _socket.open(udp::v4());
    _socket.set_option(boost::asio::socket_base::broadcast(true));
}

UdpClient::~UdpClient()
{
    _socket.close();
}

void UdpClient::sendMessage(const std::string& msg)
{
    _socket.send_to(boost::asio::buffer(msg, msg.size()), _remoteEndpoint);
}