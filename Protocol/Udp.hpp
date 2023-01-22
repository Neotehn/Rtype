#ifndef PROTOCOL_UDP_HPP_
#define PROTOCOL_UDP_HPP_

#include <memory>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <string>
#include <iostream>

#include "IProtocol.hpp"

using boost::asio::ip::udp

class Udp : public IProtocol {
    public:
        Udp(boost::asio::io_service &io_service);
        ~Udp();

    private:
        void startListening();
        void handleListening(const boost::system::error_code& error, std::size_t bytes_transferred);
        void handleSend(std::shared_ptr<std::string> msg, const boost::system::error_code& ec, std::size_t bytes_transferred);

        udp::socket _socket;
        udp::endpoint _remoteEndpoint;
        std::array<char, 1024> _recvBuffer;

    
};

#endif /* !PROTOCOL_UDP_HPP_ */