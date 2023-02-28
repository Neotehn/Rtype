#include "./CreateLobbyAction.hpp"

CreateLobbyAction::CreateLobbyAction(EntityID t_id, std::string t_lobby_ip,
                                     std::string t_player_name)
    : Action(ActionType::CREATELOBBY, t_id) {
  m_player_name = t_player_name;
  m_lobby_ip = t_lobby_ip;
}

CreateLobbyAction::CreateLobbyAction(EntityID t_id, std::string t_lobby_ip,
                                     std::string t_player_name, int action_id)
    : Action(ActionType::CREATELOBBY, action_id) {
  m_id = t_id;
  m_player_name = t_player_name;
  m_lobby_ip = t_lobby_ip;
}