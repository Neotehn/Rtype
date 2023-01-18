#ifndef PROTOCOL_UDP_HPP_
#define PROTOCOL_UDP_HPP_

#include <memory>

#include "IProtocol.hpp"

class Udp : public IProtocol {
    public:
        Udp();
        ~Udp();
    
};

#endif /* !PROTOCOL_UDP_HPP_ */