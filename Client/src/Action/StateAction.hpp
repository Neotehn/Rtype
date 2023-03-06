#ifndef R_TYPE_CLIENT_STATEACTION_HPP
#define R_TYPE_CLIENT_STATEACTION_HPP

#include <string>

#include "Action.hpp"

class StateAction : public Action {
 public:
  StateAction(ActionType t_type, EntityID t_id = 0,
              bool t_triggered_by_user = false);
  StateAction(ActionType t_type, EntityID t_id, std::string lobby_code);
  StateAction(ActionType t_type, EntityID t_id, int t_action_id);
  StateAction(ActionType t_type, EntityID t_id, int t_action_id,
              int t_player_id);
  StateAction(ActionType t_type, EntityID t_id, int t_action_id,
              std::string t_lobby_code, int t_player_id);
  StateAction(ActionType t_type, EntityID t_id, std::string t_lobby_code,
              std::string t_player_name);
  StateAction(ActionType t_type, EntityID t_id, int t_action_id,
              std::string t_lobby_code, int t_player_id, std::string t_name);
  ~StateAction() override = default;
};

#endif  //R_TYPE_CLIENT_STATEACTION_HPP
