#include "./ServerChadFilter.hpp"

ServerChadFilter::ServerChadFilter() {}

ServerChadFilter::~ServerChadFilter() {}

int ServerChadFilter::returnRandomComplimentIndex() {
  typedef boost::mt19937 RNGType;
  RNGType rng;
  boost::uniform_int<> random_good_word(0, 219);
  boost::variate_generator<RNGType, boost::uniform_int<>> good_boy_generator(
    rng, random_good_word);
  int index = good_boy_generator();
  bool found = true;
  bool check = false;

  while (found) {
    check = false;
    for (int i = 0; i < m_already_taken_compliments.size(); i++) {
      if (m_already_taken_compliments[i] == index) {
        index = good_boy_generator();
        check = true;
        break;
      }
    }
    if (!check) {
      found = false;
      m_already_taken_compliments.push_back(index);
      return index;
    }
  }
  return 0;
}

std::string ServerChadFilter::chadFiltering(std::string t_potential_bad_msg) {
  std::ifstream file_bad_words("../Server/src/Data/insults.txt");
  std::vector<std::string> insults;
  std::vector<std::string> potential_bad_word;
  std::vector<std::string> username;

  boost::split(potential_bad_word, t_potential_bad_msg, boost::is_any_of(" "));
  boost::split(username, t_potential_bad_msg, boost::is_any_of(":"));

  if (file_bad_words.is_open()) {
    std::string bad_line;

    while (std::getline(file_bad_words, bad_line)) {
      for (std::string bad_word : potential_bad_word) {
        if (bad_line == bad_word) {
          std::ifstream file_good_words("../Server/src/Data/compliments.txt");

          if (file_good_words.is_open()) {
            std::string good_line;
            int index = 0;
            int index_good_sentence = returnRandomComplimentIndex();

            while (std::getline(file_good_words, good_line)) {
              if (index == index_good_sentence) {
                std::string new_msg = username[0] + ": " + good_line;
                file_good_words.close();
                file_bad_words.close();
                return new_msg;
              }
              index += 1;
            }
            file_good_words.close();
          } else {
            return "I'm a looser";
          }
        }
      }
    }
    file_bad_words.close();
  }
  return t_potential_bad_msg;
}