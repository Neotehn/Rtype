#include "IoService.hpp"

rtype::IoService::IoService() : m_io_service() {}

void rtype::IoService::run() { m_io_service.run(); }

void rtype::IoService::stop() { m_io_service.stop(); }

boost::asio::io_service &rtype::IoService::getIoService() {
  return m_io_service;
}
