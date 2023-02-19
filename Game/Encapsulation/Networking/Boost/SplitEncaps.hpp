#ifndef R_TYPE_CLIENT_SPLITENCAPS_HPP
#define R_TYPE_CLIENT_SPLITENCAPS_HPP

#include <boost/algorithm/string.hpp>

namespace rtype {
  void split_command(std::vector<std::string> &t_result,
                     const std::string &t_string,
                     const std::string &t_delimiter) {
    boost::split(t_result, t_string, boost::is_any_of(t_delimiter));
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_SPLITENCAPS_HPP
