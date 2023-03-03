#ifndef R_TYPE_CLIENT_LEAVELOBBYACTION_HPP
#define R_TYPE_CLIENT_LEAVELOBBYACTION_HPP

#include <string>

#include "Action.hpp"

class LeaveLobbyAction : public Action {
 public:
  LeaveLobbyAction(EntityID t_id, std::string t_lobby_ip,
                   std::string t_player_name);
  LeaveLobbyAction(EntityID t_id, std::string t_lobby_ip,
                   std::string t_player_name, int action_id);

  ~LeaveLobbyAction() = default;
};

#endif  //R_TYPE_CLIENT_LEAVELOBBYACTION_HPP
