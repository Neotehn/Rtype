#include "./JoinLobbyAction.hpp"

JoinLobbyAction::JoinLobbyAction(EntityID t_id, std::string t_lobby_ip,
                                 int t_lobby_id, std::string t_player_name)
    : Action(ActionType::JOINLOBBY, t_id) {
  m_lobby_id = t_lobby_id;
  m_player_name = t_player_name;
  m_lobby_ip = t_lobby_ip;
}

JoinLobbyAction::JoinLobbyAction(EntityID t_id, std::string t_lobby_ip,
                                 int t_lobby_id, std::string t_player_name,
                                 int action_id)
    : Action(ActionType::JOINLOBBY, action_id) {
  m_id = t_id;
  m_lobby_id = t_lobby_id;
  m_player_name = t_player_name;
  m_lobby_ip = t_lobby_ip;
}
