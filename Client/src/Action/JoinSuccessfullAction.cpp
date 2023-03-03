#include "./JoinSuccessfullAction.hpp"

JoinSuccessfullAction::JoinSuccessfullAction(
  EntityID t_id, std::vector<std::string> t_player_names)
    : Action(ActionType::JOINSUCCESSFULL, t_id) {
  m_lobby_player_names = t_player_names;
}

JoinSuccessfullAction::JoinSuccessfullAction(
  EntityID t_id, std::vector<std::string> t_player_names, int action_id)
    : Action(ActionType::JOINSUCCESSFULL, action_id) {
  m_id = t_id;
  m_lobby_player_names = t_player_names;
}
