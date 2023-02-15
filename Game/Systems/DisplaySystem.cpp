#include "DisplaySystem.hpp"

DisplaySystem::DisplaySystem(std::shared_ptr<EntityManager> t_em,
                             rtype::IRenderWindow *t_window) {
  m_em = t_em;
  m_window = t_window;
}

DisplaySystem::~DisplaySystem() {}

void DisplaySystem::update() {
  m_window->clear();
  for (EntityID ent : EntityViewer<BackgroundLayer>(*m_em.get())) {
    BackgroundLayer *background = (*m_em.get()).Get<BackgroundLayer>(ent);
    m_window->draw(*background->sprite.getSprite());
  }
  for (EntityID ent : EntityViewer<Player>(*m_em.get())) {
    Player *player = (*m_em.get()).Get<Player>(ent);
    m_window->draw(player->body);
    m_window->draw(player->health.body);
  }
  for (EntityID ent : EntityViewer<Bullet>(*m_em.get())) {
    Bullet *bullet = (*m_em.get()).Get<Bullet>(ent);
    m_window->draw(bullet->body);
  }
  for (EntityID ent : EntityViewer<AnimationObj>(*m_em.get())) {
    AnimationObj *anim = (*m_em.get()).Get<AnimationObj>(ent);
    m_window->draw(anim->body);
  }

  m_window->display();
}

void DisplaySystem::updateData(SystemData &t_data) {}
