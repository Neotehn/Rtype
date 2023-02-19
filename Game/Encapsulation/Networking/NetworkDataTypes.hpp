#ifndef R_TYPE_CLIENT_NETWORKDATATYPES_HPP
#define R_TYPE_CLIENT_NETWORKDATATYPES_HPP

#include <string>

namespace rtype {
  class endpoint {
   public:
    endpoint() = default;

    endpoint(const std::string &t_address, const std::string &t_port) {
      m_address = t_address;
      m_port = t_port;
    }

    std::string address() const { return m_address; }
    std::string port() const { return m_port; }

   private:
    std::string m_address;
    std::string m_port;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_NETWORKDATATYPES_HPP
