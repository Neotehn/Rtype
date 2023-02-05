#include "PosAction.hpp"

PosAction::PosAction(EntityID t_id, sf::Vector2f t_pos)
    : Action(ActionType::POS, t_id) {
  m_position = t_pos;
}

PosAction::PosAction(EntityID t_id, sf::Vector2f t_pos, int t_action_id)
    : Action(ActionType::POS, t_id, t_action_id) {
  m_position = t_pos;
}
