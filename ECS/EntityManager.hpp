#ifndef ECS_ENTITYMANAGER_HPP_
#define ECS_ENTITYMANAGER_HPP_

#include <vector>

#include "ECS.hpp"
#include "DataTypesECS.hpp"
#include "ComponentPool.hpp"

class EntityManager
{
 public:
  struct EntityDesc
  {
    EntityID id;
    ComponentMask mask;
  };
  EntityManager() {};
  ~EntityManager() {};

  EntityID createNewEntity() {
    if (!freeEntities.empty()) {
      EntityIndex newIndex = freeEntities.back();
      freeEntities.pop_back();
      EntityID newID = CreateEntityId(newIndex, GetEntityVersion(entities[newIndex].id));
      entities[newIndex].id = newID;
      return entities[newIndex].id;
    }
    entities.push_back({ CreateEntityId(EntityIndex(entities.size()), 0), ComponentMask() });
    return entities.back().id;
  }
  void destroyEntity(EntityID id) {
    EntityID newID = CreateEntityId(EntityIndex(-1), GetEntityVersion(id) + 1);
    entities[GetEntityIndex(id)].id = newID;
    entities[GetEntityIndex(id)].mask.reset();
    freeEntities.push_back(GetEntityIndex(id));
  }

  template<typename T>
  T* Assign(EntityID id, T value) {
    int componentId = GetId<T>();

    if (componentPools.size() <= componentId) // Not enough component pool
      componentPools.resize(componentId + 1);
    if (componentPools[componentId] == nullptr) // New component, make a new pool
      componentPools[componentId] = new ComponentPool(sizeof(T));

    // Looks up the component in the pool, and initializes it with placement new
    T *pComponent = new (componentPools[componentId]->get(GetEntityIndex(id))) T(value);

    // Set the bit for this component to true and return the created component
    entities[GetEntityIndex(id)].mask.set(componentId);
    return pComponent;
  }

  template<typename T>
  T* Get(EntityID id) {
    int componentId = GetId<T>();
    if (!entities[GetEntityIndex(id)].mask.test(componentId))
      return nullptr;

    T *pComponent = static_cast<T *>(componentPools[componentId]->get(GetEntityIndex(id)));
    return pComponent;
  }
  template<typename T>
  void remove(EntityID id) {
    // ensures you're not accessing an entity that has been deleted
    if (entities[GetEntityIndex(id)].id != id)
      return;

    int componentId = GetId<T>();
    entities[GetEntityIndex(id)].mask.reset(componentId);
  }

  std::vector<EntityDesc> getEntities() { return entities; };
  std::vector<ComponentPool *> getComponentPools() { return componentPools; };

 private:
  std::vector<EntityDesc> entities;
  std::vector<ComponentPool *> componentPools;
  std::vector<EntityIndex> freeEntities;

};

#endif  // ECS_ENTITYMANAGER_HPP_
