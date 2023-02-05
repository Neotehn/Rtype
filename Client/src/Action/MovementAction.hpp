#ifndef R_TYPE_CLIENT_MOVEMENTACTION_HPP
#define R_TYPE_CLIENT_MOVEMENTACTION_HPP

#include <string>

#include "Action.hpp"

class MovementAction : public Action {
 public:
  MovementAction(ActionType t_type, EntityID t_id, bool t_triggered_by_user);
  MovementAction(ActionType t_type, EntityID t_id, bool t_triggered_by_user,
                 int t_action_id);
  ~MovementAction() override = default;
};

#endif  //R_TYPE_CLIENT_MOVEMENTACTION_HPP
