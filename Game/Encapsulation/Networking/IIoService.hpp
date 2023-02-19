#ifndef R_TYPE_CLIENT_IIOSERVICE_HPP
#define R_TYPE_CLIENT_IIOSERVICE_HPP

namespace rtype {
  class IIoService {
   public:
    virtual ~IIoService() = default;
    virtual void run() = 0;
    virtual void stop() = 0;

    // TODO: remove again
    virtual boost::asio::io_service &getIoService() = 0;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_IIOSERVICE_HPP
