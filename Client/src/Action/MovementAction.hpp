#ifndef R_TYPE_CLIENT_MOVEMENTACTION_HPP
#define R_TYPE_CLIENT_MOVEMENTACTION_HPP

#include "IAction.hpp"

class MovementAction : public IAction {
  public:
    MovementAction(ActionType t_type, EntityID t_id);
    ~MovementAction() override = default;

    std::string getCommand() const override;
};

#endif  //R_TYPE_CLIENT_MOVEMENTACTION_HPP
