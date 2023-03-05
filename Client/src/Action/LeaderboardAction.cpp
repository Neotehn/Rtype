#include "LeaderboardAction.hpp"

LeaderboardAction::LeaderboardAction(EntityID t_id, EntityID t_player_id) :
  Action(ActionType::ASKLEADERBOARD, t_id) {
  ;
}

LeaderboardAction::LeaderboardAction(EntityID t_id,
                                     std::vector<std::string> t_leaderboard)
    :Action(ActionType::SENDLEADERBOARD, t_id) {
  m_leaderboard = t_leaderboard;
}
