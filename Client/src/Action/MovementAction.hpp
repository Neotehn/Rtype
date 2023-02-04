#ifndef R_TYPE_CLIENT_MOVEMENTACTION_HPP
#define R_TYPE_CLIENT_MOVEMENTACTION_HPP

#include <string>

#include "IAction.hpp"

class MovementAction : public IAction {
 public:
  MovementAction(ActionType t_type, EntityID t_id);
  MovementAction(ActionType t_type, EntityID t_id, int t_action_id);
  ~MovementAction() override = default;

  std::string getCommand() const override;
};

#endif  //R_TYPE_CLIENT_MOVEMENTACTION_HPP
