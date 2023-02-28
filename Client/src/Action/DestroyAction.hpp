#ifndef R_TYPE_CLIENT_DESTROYACTION_HPP
#define R_TYPE_CLIENT_DESTROYACTION_HPP

#include <string>

#include "Action.hpp"

class DestroyAction : public Action {
 public:
  DestroyAction(EntityID t_id);
  DestroyAction(EntityID t_id, int t_action_id);

  ~DestroyAction() = default;
};

#endif  //R_TYPE_CLIENT_DESTROYACTION_HPP
