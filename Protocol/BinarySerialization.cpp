#include "./BinarySerialization.hpp"

BinarySerialization::BinarySerialization() {
  m_message_lenght = 0;
  m_data.check_sum = 0;
  m_data.destination_port = 0;
  m_data.lenght = 0;
  m_data.source_port = 0;
  m_data.message = "";
}

BinarySerialization::~BinarySerialization() {}

BinaryData BinarySerialization::getData() const { return m_data; }

std::string
BinarySerialization::deserializationMessage(std::array<char, 1024> t_buffer,
                                            std::size_t t_buffer_lenght) {}