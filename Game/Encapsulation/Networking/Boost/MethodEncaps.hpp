#ifndef R_TYPE_CLIENT_METHODENCAPS_HPP
#define R_TYPE_CLIENT_METHODENCAPS_HPP

#include <string>
#include <thread>
#include <chrono>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "ErrorCode.hpp"

namespace rtype {
  void thread_sleep(int t_milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(t_milliseconds));
  };

  template<typename T>
  auto bind(void (T::*t_method)(const rtype::ErrorCode &, std::size_t),
            T *t_class) {
    return boost::bind(t_method, t_class, boost::asio::placeholders::error,
                       boost::asio::placeholders::bytes_transferred);
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_METHODENCAPS_HPP
