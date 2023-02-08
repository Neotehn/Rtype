#ifndef R_TYPE_CLIENT_INCREASEACTION_HPP
#define R_TYPE_CLIENT_INCREASEACTION_HPP

#include <string>

#include "Action.hpp"

class IncreaseAction : public Action {
 public:
  IncreaseAction(EntityID t_id, IncreaseType t_type, int t_value);
  IncreaseAction(EntityID t_id, IncreaseType t_type, int t_value,
                 int t_action_id);
  ~IncreaseAction() override = default;
};

#endif  //R_TYPE_CLIENT_INCREASEACTION_HPP
