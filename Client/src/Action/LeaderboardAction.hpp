#ifndef R_TYPE_CLIENT_LEADERBOARDACTION_HPP
#define R_TYPE_CLIENT_LEADERBOARDACTION_HPP

#include "Action.hpp"

class LeaderboardAction : public Action {
 public:
  LeaderboardAction(EntityID t_id, EntityID t_player_id);  // constructor server
  //GetLeaderboardAction(EntityID t_id, int t_action_id, EntityID t_player_id);
  LeaderboardAction(
    EntityID t_id,
    std::vector<std::string> t_leaderboard);  // constructor client
  ~LeaderboardAction() = default;
};

#endif  //R_TYPE_CLIENT_LEADERBOARDACTION_HPP
