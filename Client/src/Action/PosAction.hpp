#ifndef R_TYPE_CLIENT_POSACTION_HPP
#define R_TYPE_CLIENT_POSACTION_HPP

#include <string>

#include "Action.hpp"

class PosAction : public Action {
 public:
  PosAction(EntityID t_id, sf::Vector2f t_pos);
  PosAction(EntityID t_id, sf::Vector2f t_pos, int t_action_id);
  ~PosAction() = default;
};

#endif  //R_TYPE_CLIENT_POSACTION_HPP
