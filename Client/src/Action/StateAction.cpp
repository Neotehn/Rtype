#include "StateAction.hpp"

StateAction::StateAction(ActionType t_type, EntityID t_id,
                         bool t_triggered_by_user)
    : Action(t_type, t_id) {
  m_triggered_by_user = t_triggered_by_user;
}

StateAction::StateAction(ActionType t_type, EntityID t_id,
                         std::string t_lobby_code)
    : Action(t_type, t_id) {
  m_lobby_ip = t_lobby_code;
}

StateAction::StateAction(ActionType t_type, EntityID t_id,
                         std::string t_lobby_code, std::string t_player_name)
    : Action(t_type, t_id) {
  m_lobby_ip = t_lobby_code;
  m_player_name = t_player_name;
}

StateAction::StateAction(ActionType t_type, EntityID t_id, int t_action_id)
    : Action(t_type, t_id, t_action_id) {
  m_triggered_by_user = false;
}

StateAction::StateAction(ActionType t_type, EntityID t_id, int t_action_id,
                         int t_player_id)
    : Action(t_type, t_id, t_action_id) {
  m_client_id = t_player_id;
}

StateAction::StateAction(ActionType t_type, EntityID t_id, int t_action_id,
                         std::string t_lobby_code, int t_player_id)
    : Action(t_type, t_id, t_action_id) {
  m_lobby_ip = t_lobby_code;
  m_client_id = t_player_id;
}

StateAction::StateAction(ActionType t_type, EntityID t_id, int t_action_id,
                         std::string t_lobby_code, int t_player_id,
                         std::string t_name)
    : Action(t_type, t_id, t_action_id) {
  m_lobby_ip = t_lobby_code;
  m_client_id = t_player_id;
  setPlayerName(t_name);
}
