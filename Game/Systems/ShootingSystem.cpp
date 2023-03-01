#include "ShootingSystem.hpp"

ShootingSystem::ShootingSystem(std::shared_ptr<EntityManager> t_em,
                               UdpServer *t_serverCom,
                               rtype::IGraphicLoader *t_graphic_loader) {
  m_em = t_em;
  m_serverCom = t_serverCom;
  m_graphic_loader = t_graphic_loader;
}

void ShootingSystem::updateData(SystemData &t_data) {
  m_event_queue = t_data.event_queue;
}

void ShootingSystem::update() {
  for (std::shared_ptr<Action> action :
       m_event_queue.getAllOfType(Action::ActionType::SHOOT)) {
    for (EntityID ent : EntityViewer<Player>(*m_em)) {
      if (ent != action->getId()) continue;

      switch (action->getShootType()) {
        case Action::ShootingType::NORMAL:
          initShoot(action, m_em, m_graphic_loader, m_serverCom);
          break;
        case Action::ShootingType::COIN:
          shootMoney(action);
          break;
        case Action::ShootingType::FIRE:
          shootFire(action);
          break;
        case Action::ShootingType::BOMB:
          shootBomb(action);
          break;
        default:
          break;
      }
    }
  }
}

void ShootingSystem::shootMoney(std::shared_ptr<Action> t_action) {
  Player *player = (*m_em).Get<Player>(t_action->getId());

  if (player->coin_shot == 0) return;
  player->coin_shot -= 1;
  if (player->coin_shot < 0) player->coin_shot = 0;

  initCoinShoot(t_action, m_em, m_graphic_loader, m_serverCom);
}

void ShootingSystem::shootFire(std::shared_ptr<Action> t_action) {
  Player *player = (*m_em).Get<Player>(t_action->getId());

  if (player->fire_shot == 0) return;
  player->fire_shot -= 1;
  if (player->fire_shot < 0) player->fire_shot = 0;

  initFireShoot(t_action, m_em, m_graphic_loader, m_serverCom);
}

void ShootingSystem::shootBomb(std::shared_ptr<Action> t_action) {
  Player *player = (*m_em).Get<Player>(t_action->getId());

  if (player->bomb_shot == 0) return;
  player->bomb_shot -= 1;
  if (player->bomb_shot < 0) player->bomb_shot = 0;

  initBombShoot(t_action, m_em, m_graphic_loader, m_serverCom);
}
