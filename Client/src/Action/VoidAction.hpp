#ifndef R_TYPE_CLIENT_VOIDACTION_HPP
#define R_TYPE_CLIENT_VOIDACTION_HPP

#include <string>

#include "IAction.hpp"

class VoidAction : public IAction {
 public:
  VoidAction(EntityID t_id, int t_action_id);
  ~VoidAction() override = default;

  std::string getCommand() const override;
};

#endif  //R_TYPE_CLIENT_VOIDACTION_HPP
