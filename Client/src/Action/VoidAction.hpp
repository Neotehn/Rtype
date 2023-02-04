#ifndef R_TYPE_CLIENT_VOIDACTION_HPP
#define R_TYPE_CLIENT_VOIDACTION_HPP

#include <string>

#include "Action.hpp"

class VoidAction : public Action {
 public:
  VoidAction(EntityID t_id, int t_action_id);
  ~VoidAction() override = default;
};

#endif  //R_TYPE_CLIENT_VOIDACTION_HPP
