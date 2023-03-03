#include "ChadAction.hpp"

ChadAction::ChadAction(EntityID t_id, std::string t_chat_msg,
                       std::string t_lobby_code)
    : Action(ActionType::CHAD, t_id) {
  m_chad_msg = t_chat_msg;
  m_lobby_ip = t_lobby_code;
}

ChadAction::ChadAction(EntityID t_id, std::string t_chat_msg,
                       std::string t_lobby_code, int t_action_id)
    : Action(ActionType::CHAD, t_id, t_action_id) {
  m_chad_msg = t_chat_msg;
  m_lobby_ip = t_lobby_code;
}
