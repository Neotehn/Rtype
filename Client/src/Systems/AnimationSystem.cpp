#include "AnimationSystem.hpp"

AnimationSystem::AnimationSystem(std::shared_ptr<EntityManager> t_em) {
  m_em = t_em;
}

AnimationSystem::~AnimationSystem() {}

void AnimationSystem::updateData(SystemData& t_data) {}

void AnimationSystem::update() {
  if (m_clock.getElapsedTime().asSeconds() < 0.1) {
    return;
  }
  for (EntityID ent :
       EntityViewer<std::string, Pos, sf::RectangleShape>(*m_em.get())) {
    sf::RectangleShape* shape = (*m_em.get()).Get<sf::RectangleShape>(ent);
    sf::IntRect rect = shape->getTextureRect();
    if (rect.left >= 68) {
      rect.left = 0;
    } else {
      rect.left += 34;
    }
    std::cout << rect.left << std::endl;
    shape->setTextureRect(rect);
  }
  m_clock.restart();
}
