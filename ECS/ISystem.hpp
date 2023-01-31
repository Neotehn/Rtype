#ifndef ECS_ISYSTEM_HPP_
#define ECS_ISYSTEM_HPP_

#include <memory>
#include "../ECS/EntityViewer.hpp"
#include "../ECS/DataTypesECS.hpp"

class ISystem {
 public:
  ~ISystem() = default;
  virtual void update() = 0;
  virtual void updateData(SystemData &t_data) = 0;

 protected:
  std::shared_ptr<EntityManager> m_em;
};

#endif  // ECS_ISYSTEM_HPP_
