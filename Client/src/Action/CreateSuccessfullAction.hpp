#ifndef R_TYPE_CLIENT_CREATESUCCESSFULLACTION_HPP
#define R_TYPE_CLIENT_CREATESUCCESSFULLACTION_HPP

#include <string>

#include "Action.hpp"

class CreateSuccessfullAction : public Action {
 public:
  CreateSuccessfullAction(EntityID t_id);
  CreateSuccessfullAction(EntityID t_id, int action_id);

  ~CreateSuccessfullAction() = default;
};

#endif  //R_TYPE_CLIENT_CREATESUCCESSFULLACTION_HPP
