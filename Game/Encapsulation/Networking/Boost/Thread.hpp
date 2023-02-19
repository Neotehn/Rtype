#ifndef R_TYPE_CLIENT_THREAD_HPP
#define R_TYPE_CLIENT_THREAD_HPP

#include <boost/asio.hpp>

// TODO: muss noch implementiert und getestet werden
namespace rtype {
  class Thread {
   public:
    Thread(auto f) : m_thread(f){};
    ~Thread() = default;

   private:
    std::thread m_thread;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_THREAD_HPP
