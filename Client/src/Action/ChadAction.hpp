#ifndef R_TYPE_CLIENT_CHADACTION_HPP
#define R_TYPE_CLIENT_CHADACTION_HPP

#include <string>

#include "Action.hpp"

class ChadAction : public Action {
 public:
  ChadAction(EntityID t_id, std::string t_chat_msg, std::string t_lobby_code);
  ChadAction(EntityID t_id, std::string t_chat_msg, std::string t_lobby_code,
             int t_action_id);
  ~ChadAction() = default;
};

#endif  //R_TYPE_CLIENT_CHADACTION_HPP
