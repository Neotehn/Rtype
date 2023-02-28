#ifndef ECS_ISYSTEM_HPP_
#define ECS_ISYSTEM_HPP_

#include <memory>
#include "EntityViewer.hpp"
#include "DataTypesECS.hpp"
#include "../Encapsulation/GraphicDataTypes.hpp"
#include "../Encapsulation/IRectangleShape.hpp"
#include "../Encapsulation/IGraphicLoader.hpp"

class ISystem {
 public:
  ~ISystem() = default;
  virtual void update() = 0;
  virtual void updateData(SystemData &t_data) = 0;

 protected:
  std::shared_ptr<EntityManager> m_em;
};

#endif  // ECS_ISYSTEM_HPP_
