#ifndef R_TYPE_CLIENT_JOINLOBBYACTION_HPP
#define R_TYPE_CLIENT_JOINLOBBYACTION_HPP

#include <string>

#include "Action.hpp"

class JoinLobbyAction : public Action {
 public:
  JoinLobbyAction(EntityID t_id, std::string t_lobby_ip, int t_lobby_id,
                  std::string t_player_name);
  JoinLobbyAction(EntityID t_id, std::string t_lobby_ip, int t_lobby_id,
                  std::string t_player_name, int action_id);

  ~JoinLobbyAction() = default;
};

#endif  //R_TYPE_CLIENT_JOINLOBBYACTION_HPP
