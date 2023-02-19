#include "./UdpSession.hpp"

UdpSession::UdpSession(UdpServer *t_server) : m_server(t_server) {}

void UdpSession::handleSent(const rtype::ErrorCode &t_ec, std::size_t) {
  if (t_ec) {
    std::cout << "Error sending response to " << m_remoteEndpoint << ": "
              << t_ec.message() << "\n";
  }
}