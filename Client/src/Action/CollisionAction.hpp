#ifndef R_TYPE_CLIENT_COLLISIONACTION_HPP
#define R_TYPE_CLIENT_COLLISIONACTION_HPP

#include <string>

#include "Action.hpp"

class CollisionAction : public Action {
 public:
  CollisionAction(EntityID t_id, EntityID t_other_id);
  CollisionAction(EntityID t_id, EntityID t_other_id, int t_action_id);
  ~CollisionAction() = default;
};

#endif  //R_TYPE_CLIENT_COLLISIONACTION_HPP
