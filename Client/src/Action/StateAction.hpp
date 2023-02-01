#ifndef R_TYPE_CLIENT_STATEACTION_HPP
#define R_TYPE_CLIENT_STATEACTION_HPP

#include "IAction.hpp"

class StateAction : public IAction {
  public:
    StateAction(ActionType t_type, EntityID t_id);
    ~StateAction() override = default;

    std::string getCommand() const override;
};

#endif  //R_TYPE_CLIENT_STATEACTION_HPP
