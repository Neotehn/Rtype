#ifndef R_TYPE_CLIENT_SHOOTACTION_HPP
#define R_TYPE_CLIENT_SHOOTACTION_HPP

#include <string>

#include "Action.hpp"

class ShootAction : public Action {
 public:
  ShootAction(EntityID t_id, int t_damage, int t_type);
  ShootAction(EntityID t_id, int t_damage, int t_type, int t_action_id);
  ~ShootAction() override = default;
};

#endif  //R_TYPE_CLIENT_SHOOTACTION_HPP
