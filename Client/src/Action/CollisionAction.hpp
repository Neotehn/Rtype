#ifndef R_TYPE_CLIENT_COLLISIONACTION_HPP
#define R_TYPE_CLIENT_COLLISIONACTION_HPP

#include "IAction.hpp"

class CollisionAction : public IAction {
 public:
  CollisionAction(EntityID t_id, EntityID t_other_id);
  ~CollisionAction() override = default;

  std::string getCommand() const override;

  EntityID getCollisionPartnerId() const;

 private:
  EntityID m_collision_partner_id;
};

#endif  //R_TYPE_CLIENT_COLLISIONACTION_HPP
