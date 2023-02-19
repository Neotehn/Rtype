#ifndef R_TYPE_CLIENT_IOSERVICE_HPP
#define R_TYPE_CLIENT_IOSERVICE_HPP

#include <boost/asio.hpp>

#include "../IIoService.hpp"

namespace rtype {
  class IoService : public IIoService {
   public:
    IoService();
    ~IoService() override = default;

    void run() override;
    void stop() override;

    boost::asio::io_service &getIoService() override;

   private:
    boost::asio::io_service m_io_service;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_IOSERVICE_HPP
