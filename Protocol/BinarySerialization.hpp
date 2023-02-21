#ifndef PROTOCOL_BINARYSERILIZATION_HPP_
#define PROTOCOL_BINARYSERILIZATION_HPP_

#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <boost/algorithm/string/find.hpp>
#include <boost/algorithm/string.hpp>

struct BinaryData {
  unsigned short int source_port;
  unsigned short int destination_port;
  unsigned short int lenght;
  unsigned short int check_sum;
  std::string message;
};

class BinarySerialization {
 public:
  ~BinarySerialization();
  BinarySerialization();
  BinaryData getData() const;
  std::string deserializationMessage(std::array<char, 1024> t_buffer,
                                     std::size_t t_buffer_lenght);

 private:
  BinaryData m_data;
  std::size_t m_message_lenght;
};

#endif /* !PROTOCOL_BINARYSERILIZATION_HPP_ */
