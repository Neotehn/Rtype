#include "DisplaySystem.hpp"

DisplaySystem::DisplaySystem(std::shared_ptr<EntityManager> t_em,
                             rtype::IRenderWindow *t_window, std::size_t t_flag,
                             rtype::IGraphicLoader *t_graphic_loader)
    : m_gui(GUISystem(t_em, t_graphic_loader, t_window)) {
  m_em = t_em;
  m_window = t_window;
  m_flag = t_flag;
}

DisplaySystem::~DisplaySystem() {}

void DisplaySystem::update() {
  m_window->clear();
  for (EntityID ent : EntityViewer<BackgroundLayer>(*m_em.get())) {
    BackgroundLayer *background = (*m_em.get()).Get<BackgroundLayer>(ent);
    m_window->draw(background->sprite.getSprite());
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
  for (EntityID ent : EntityViewer<SpinningItem>(*m_em.get())) {
    SpinningItem *item = (*m_em.get()).Get<SpinningItem>(ent);
    m_window->draw(item->body);
  }
  if (m_flag == 1) { m_gui.update(); }
  m_window->display();
}

void DisplaySystem::updateData(SystemData &t_data) {
  if (m_flag == 1) { m_gui.updateData(t_data); }
}
