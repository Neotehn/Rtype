#include "./CreatePlayerSystem.hpp"

CreatePlayerSystem::CreatePlayerSystem(
  std::shared_ptr<EntityManager> t_em, UdpServer *t_server_com,
  rtype::IGraphicLoader *t_graphic_loader) {
  m_em = t_em;
  m_server_com = t_server_com;
  m_graphic_loader = t_graphic_loader;
}

void CreatePlayerSystem::updateData(SystemData &t_data) {
  m_event_queue = t_data.event_queue;
}

bool CreatePlayerSystem::isRegistered(int t_id) {
  if (t_id == 0) return true;
  for (int id : m_registered_players) {
    if (t_id == id) { return true; }
  }
  return false;
}

void CreatePlayerSystem::update() {
  for (std::shared_ptr<Action> action :
       m_event_queue.getAllOfType(Action::ActionType::START)) {
    if (!isRegistered(action->getId())) {
      m_registered_players.push_back(action->getId());
      EntityID player_id = initPlayer(m_em, m_server_com, m_graphic_loader);
      action->setPlayerId(player_id);
    }
  }
}
