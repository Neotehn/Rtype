#ifndef R_TYPE_CLIENT_DAMAGEACTION_HPP
#define R_TYPE_CLIENT_DAMAGEACTION_HPP

#include <string>

#include "Action.hpp"

class DamageAction : public Action {
 public:
  DamageAction(EntityID t_id, int t_damage);
  DamageAction(EntityID t_id, int t_damage, int t_action_id);

  ~DamageAction() = default;
};

#endif  //R_TYPE_CLIENT_DAMAGEACTION_HPP
