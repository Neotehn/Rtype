#ifndef R_TYPE_CLIENT_ERRORCODE_HPP
#define R_TYPE_CLIENT_ERRORCODE_HPP

#include <boost/system/error_code.hpp>

namespace rtype {
  class ErrorCode {
   public:
    ErrorCode();
    ErrorCode(int t_value, const boost::system::error_category &t_category);
    ErrorCode(const boost::system::error_code t_code);
    ~ErrorCode() = default;

    int value();
    const boost::system::error_category &category() const noexcept;
    std::string message() const;
    char const *message(char *buffer, std::size_t buffer_size) const;
    explicit operator bool() const noexcept {
      if (m_error_code) return true;
      return false;
    };

    void assign(int t_value, const boost::system::error_category &t_category);
    void clear();
    boost::system::error_condition default_error_condition() const noexcept;
    bool failed() const noexcept;

   private:
    boost::system::error_code m_error_code;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_ERRORCODE_HPP
