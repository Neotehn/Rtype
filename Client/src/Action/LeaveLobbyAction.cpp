#include "./LeaveLobbyAction.hpp"

LeaveLobbyAction::LeaveLobbyAction(EntityID t_id, std::string t_lobby_ip,
                                   std::string t_player_name)
    : Action(ActionType::LEAVELOBBY, t_id) {
  m_player_name = t_player_name;
  m_lobby_ip = t_lobby_ip;
}

LeaveLobbyAction::LeaveLobbyAction(EntityID t_id, std::string t_lobby_ip,
                                   std::string t_player_name, int action_id)
    : Action(ActionType::LEAVELOBBY, action_id) {
  m_id = t_id;
  m_player_name = t_player_name;
  m_lobby_ip = t_lobby_ip;
}