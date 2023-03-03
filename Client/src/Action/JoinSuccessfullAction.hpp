#ifndef R_TYPE_CLIENT_JOINSUCCESSFULLACTION_HPP
#define R_TYPE_CLIENT_JOINSUCCESSFULLACTION_HPP

#include <string>
#include <vector>

#include "Action.hpp"

class JoinSuccessfullAction : public Action {
 public:
  JoinSuccessfullAction(EntityID t_id, std::vector<std::string> t_player_names);
  JoinSuccessfullAction(EntityID t_id, std::vector<std::string> t_player_names,
                        int action_id);

  ~JoinSuccessfullAction() = default;
};

#endif  //R_TYPE_CLIENT_JOINSUCCESSFULLACTION_HPP
