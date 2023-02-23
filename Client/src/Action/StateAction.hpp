#ifndef R_TYPE_CLIENT_STATEACTION_HPP
#define R_TYPE_CLIENT_STATEACTION_HPP

#include <string>

#include "Action.hpp"

class StateAction : public Action {
 public:
  StateAction(ActionType t_type, EntityID t_id);
  StateAction(ActionType t_type, EntityID t_id, int t_action_id);
  StateAction(ActionType t_type, EntityID t_id, int t_action_id,
              int t_player_id);
  ~StateAction() override = default;
};

#endif  //R_TYPE_CLIENT_STATEACTION_HPP
