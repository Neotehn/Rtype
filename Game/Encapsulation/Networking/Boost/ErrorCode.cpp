#include "ErrorCode.hpp"

rtype::ErrorCode::ErrorCode() { m_error_code = boost::system::error_code(); }

rtype::ErrorCode::ErrorCode(int t_value,
                            const boost::system::error_category &t_category) {
  m_error_code = boost::system::error_code(t_value, t_category);
}

int rtype::ErrorCode::value() { return m_error_code.value(); }

const boost::system::error_category &
rtype::ErrorCode::category() const noexcept {
  return m_error_code.category();
}

std::string rtype::ErrorCode::message() const { return m_error_code.message(); }

char const *rtype::ErrorCode::message(char *buffer,
                                      std::size_t buffer_size) const {
  return m_error_code.message(buffer, buffer_size);
}

void rtype::ErrorCode::assign(int t_value,
                              const boost::system::error_category &t_category) {
  m_error_code.assign(t_value, t_category);
}

void rtype::ErrorCode::clear() { m_error_code.clear(); }

boost::system::error_condition
rtype::ErrorCode::default_error_condition() const noexcept {
  return m_error_code.default_error_condition();
}

bool rtype::ErrorCode::failed() const noexcept { return m_error_code.failed(); }

rtype::ErrorCode::ErrorCode(const boost::system::error_code t_code) {
  m_error_code = t_code;
}
