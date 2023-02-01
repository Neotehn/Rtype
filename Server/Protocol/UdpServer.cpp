#include "./UdpServer.hpp"

using boost::asio::ip::udp;

UdpServer::UdpServer(boost::asio::io_service &t_io_service)
    : m_socket(t_io_service, udp::endpoint(udp::v4(), 27000)),
      m_strand(t_io_service) {
  std::cout << "hello folk" << std::endl;
  startListening();
}

UdpServer::~UdpServer() { m_socket.close(); }

void UdpServer::startListening() {
  auto session = boost::make_shared<UdpSession>(this);

  m_socket.async_receive_from(
    boost::asio::buffer(session->m_recvBuffer), session->m_remoteEndpoint,
    m_strand.wrap(boost::bind(&UdpServer::handleListening, this, session,
                              boost::asio::placeholders::error,
                              boost::asio::placeholders::bytes_transferred)));
}

void UdpServer::handleListening(shared_session t_session,
                                const error_code &t_ec,
                                std::size_t t_bytesTransferred) {
  // now, handle the current session on any available pool thread
  boost::asio::post(m_socket.get_executor(),
                    boost::bind(&UdpSession::handleRequest, t_session, t_ec,
                                t_bytesTransferred));
  // immediately accept new datagrams
  startListening();
}

void UdpServer::enqueueResponse(shared_session const &t_session) {
  // async_send_to() is not thread-safe, so use a strand.
  boost::asio::post(m_socket.get_executor(),
                    m_strand.wrap(boost::bind(&UdpServer::enqueueResponseStrand,
                                              this, t_session)));
}

void UdpServer::enqueueResponseStrand(shared_session const &t_session) {
  t_session->m_message = "yes";
  m_socket.async_send_to(
    boost::asio::buffer(t_session->m_message), t_session->m_remoteEndpoint,
    m_strand.wrap(boost::bind(&UdpSession::handleSent, t_session,
                              boost::asio::placeholders::error,
                              boost::asio::placeholders::bytes_transferred)));
}

void UdpSession::handleRequest(const error_code &t_error,
                               std::size_t t_bytes_transferred) {
  if (!t_error || t_error == boost::asio::error::message_size) {
    std::cout << "Received: '"
              << std::string(m_recvBuffer.begin(),
                             m_recvBuffer.begin() + t_bytes_transferred)
              << "' (" << t_error.message() << ")\n";

    // let the server coordinate actual IO
    // give the message
    m_server->enqueueResponse(shared_from_this());
  }
}