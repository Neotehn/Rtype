#ifndef R_TYPE_CLIENT_JOINSUCCESSFULLACTION_HPP
#define R_TYPE_CLIENT_JOINSUCCESSFULLACTION_HPP

#include <string>

#include "Action.hpp"

class JoinSuccessfullAction : public Action {
 public:
  JoinSuccessfullAction(EntityID t_id);
  JoinSuccessfullAction(EntityID t_id, int action_id);

  ~JoinSuccessfullAction() = default;
};

#endif  //R_TYPE_CLIENT_JOINSUCCESSFULLACTION_HPP
