#ifndef ECS_ECS_HPP_
#define ECS_ECS_HPP_

#include <bitset>

extern int counter;
const int MAX_COMPONENTS = 32;
const int MAX_ENTITIES = 5000;
typedef unsigned int EntityIndex;
typedef unsigned int EntityVersion;
typedef unsigned long long EntityID;
typedef std::bitset<MAX_COMPONENTS> ComponentMask;

template <class T>
int getId() {
  static int curCounter = counter++;
  return curCounter;
}

inline EntityID createEntityId(EntityIndex index, EntityVersion version) {
  // Shift the index up 32, and put the version in the bottom
  return ((EntityID)index << 32) | ((EntityID)version);
}
inline EntityIndex getEntityIndex(EntityID t_id) {
  // Shift down 32 so we lose the version and get our index
  return t_id >> 32;
}
inline EntityVersion getEntityVersion(EntityID t_id) {
  // Cast to a 32 bit int to get our version number (loosing the top 32 bits)
  return (EntityVersion)t_id;
}
inline bool isEntityValid(EntityID t_id) {
  // Check if the index is our invalid index
  return (t_id >> 32) != EntityIndex(-1);
}

#define INVALID_ENTITY CreateEntityId(EntityIndex(-1), 0)

#endif  // ECS_ECS_HPP_
