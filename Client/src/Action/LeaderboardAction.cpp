#include "LeaderboardAction.hpp"

LeaderboardAction::LeaderboardAction(EntityID t_id, EntityID t_player_id) :
  Action(ActionType::ASKLEADERBOARD, t_id) {
  ;
}