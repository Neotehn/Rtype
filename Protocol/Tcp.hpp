#ifndef PROTOCOL_TCP_HPP_
#define PROTOCOL_TCP_HPP_

#include <memory>

#include "IProtocol.hpp"

class Tcp : public IProtocol 
{
  public:
    Tcp();
    ~Tcp();
    
};

#endif /* !PROTOCOL_TCP_HPP_ */
