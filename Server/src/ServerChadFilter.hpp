#ifndef PROTOCOL_SERVERCHADFILTER_HPP_
#define PROTOCOL_SERVERCHADFILTER_HPP_

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include <fstream>
#include <vector>
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"
#include <boost/algorithm/string.hpp>

class ServerChadFilter {
 public:
  ServerChadFilter();
  ~ServerChadFilter();

  std::string chadFiltering(std::string t_potential_bad_msg);
  int returnRandomComplimentIndex();

 private:
  std::vector<int> m_already_taken_compliments;
};

#endif /* !PROTOCOL_SERVERCHADFILTER_HPP_ */