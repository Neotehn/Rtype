#ifndef ECS_ENTITYVIEWER_HPP_
#define ECS_ENTITYVIEWER_HPP_

#include "EntityManager.hpp"

template<typename... ComponentTypes>
class EntityViewer {
 public:
  EntityViewer(EntityManager &scene) : m_entityManager(&scene), all(false) {
    if (sizeof...(ComponentTypes) == 0) {
      all = true;
    } else {
      // Unpack the template parameters into an initializer list
      int componentIds[] = {0, getId<ComponentTypes>()...};
      for (int i = 1; i < (sizeof...(ComponentTypes) + 1); i++)
        m_componentMask.set(componentIds[i]);
    }
  }

  class Iterator {
   public:
    Iterator(EntityManager *entityManager, EntityIndex index,
             ComponentMask mask, bool all)
        : m_entityManagerI(entityManager), m_index(index), m_mask(mask),
          all(all) {}

    EntityID operator*() const {
      return m_entityManagerI->getEntities()[m_index].id;
    }

    bool operator==(const Iterator &other) const {
      return m_index == other.m_index ||
             m_index == m_entityManagerI->getEntities().size();
    }

    bool operator!=(const Iterator &other) const {
      return m_index != other.m_index &&
             m_index != m_entityManagerI->getEntities().size();
    }

    bool ValidIndex() {
      bool validEntityID =
        isEntityValid(m_entityManagerI->getEntities()[m_index].id);
      bool correctComponentMask =
        (all ||
         m_mask == (m_mask & m_entityManagerI->getEntities()[m_index].mask));
      return validEntityID && correctComponentMask;
    }

    Iterator &operator++() {
      do {
        m_index++;
      } while (m_index < m_entityManagerI->getEntities().size() &&
               !ValidIndex());
      return *this;
    }

   private:
    EntityIndex m_index;
    EntityManager *m_entityManagerI;
    ComponentMask m_mask;
    bool all{false};
  };

  const Iterator begin() const {
    int firstIndex = 0;
    while (
      firstIndex < m_entityManager->getEntities().size() &&
      (m_componentMask !=
         (m_componentMask & m_entityManager->getEntities()[firstIndex].mask) ||
       !isEntityValid(m_entityManager->getEntities()[firstIndex].id))) {
      firstIndex++;
    }
    return Iterator(m_entityManager, firstIndex, m_componentMask, all);
  }

  const Iterator end() const {
    return Iterator(m_entityManager,
                    EntityIndex(m_entityManager->getEntities().size()),
                    m_componentMask, all);
  }

 private:
  EntityManager *m_entityManager;
  ComponentMask m_componentMask;
  // will iterate all entities if no ComponentType specified
  bool all;
};

#endif  // ECS_ENTITYVIEWER_HPP_
