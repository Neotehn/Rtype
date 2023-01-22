#include "Udp.hpp"

Udp::Udp(boost::asio::io_service &io_service)
{
    _socket(io_service, udp::endpoint(udp::v4(), 1111))
    startListening();
}

Udp::startListening()
{
    _socket.async_receive_from(boost::asio::buffer(_recvBuffer), _remoteEndpoint,
        boost::bind(&Udp::handleListening, this, 
        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

Udp::handleSend(std::shared_ptr<std::string> msg, const boost::system::error_code& ec, std::size_t bytes_transferred)
{
    startListening();
}

Udp::handleListening(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (!error ||  error == boost::asio::error::message_size) {
        auto message = std::make_shared<std::string>("Hello\n");

        _socket.async_send_to(boost::asio::buffer(*message), _remoteEndpoint,
            boost::bind(&Udp::handleSend, this, message,
            boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }
}