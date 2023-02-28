#ifndef R_TYPE_CLIENT_CREATELOBBYACTION_HPP
#define R_TYPE_CLIENT_CREATELOBBYACTION_HPP

#include <string>

#include "Action.hpp"

class CreateLobbyAction : public Action {
 public:
  CreateLobbyAction(EntityID t_id, std::string t_lobby_ip,
                    std::string t_player_name);
  CreateLobbyAction(EntityID t_id, std::string t_lobby_ip,
                    std::string t_player_name, int action_id);

  ~CreateLobbyAction() = default;
};

#endif  //R_TYPE_CLIENT_CREATELOBBYACTION_HPP
