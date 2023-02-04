#ifndef R_TYPE_CLIENT_STATEACTION_HPP
#define R_TYPE_CLIENT_STATEACTION_HPP

#include <string>

#include "IAction.hpp"

class StateAction : public IAction {
 public:
  StateAction(ActionType t_type, EntityID t_id);
  StateAction(ActionType t_type, EntityID t_id, int t_action_id);
  ~StateAction() override = default;

  std::string getCommand() const override;
};

#endif  //R_TYPE_CLIENT_STATEACTION_HPP
