#include "DisplaySystem.hpp"

DisplaySystem::DisplaySystem(std::shared_ptr<EntityManager> t_em, sf::RenderWindow &t_window) {
    m_em = t_em;
    m_window = &t_window;
}

DisplaySystem::~DisplaySystem() {}

void DisplaySystem::update() {
    m_window->clear();
    for (EntityID ent : EntityViewer<SpriteECS>(*m_em.get()))
    {
      SpriteECS* sprite = (*m_em.get()).Get<SpriteECS>(ent);
      m_window->draw(*(sprite)->getSprite());
    }

    for (EntityID ent : EntityViewer<sf::RectangleShape>(*m_em.get()))
    {
      sf::RectangleShape* sprite = (*m_em.get()).Get<sf::RectangleShape>(ent);
      m_window->draw(*sprite);
    }

    m_window->display();
}

void DisplaySystem::updateData(SystemData &t_data) {}
