#ifndef R_TYPE_CLIENT_CREATEACTION_HPP
#define R_TYPE_CLIENT_CREATEACTION_HPP

#include <string>

#include <SFML/System/Vector2.hpp>

#include "Action.hpp"

class CreateAction : public Action {
 public:
  CreateAction(EntityID t_id, ObjectType t_object_type,
               rtype::Vector2f t_position, std::string t_sprite_path);
  CreateAction(EntityID t_id, ObjectType t_object_type,
               rtype::Vector2f t_position, std::string t_sprite_path,
               int t_action_id, float t_velocity);
  CreateAction(EntityID t_id, ObjectType t_object_type,
               rtype::Vector2f t_position, std::string t_sprite_path,
               float t_velocity);
  CreateAction(EntityID t_id, ObjectType t_object_type,
               rtype::Vector2f t_position,
               Action::ShootingType t_shooting_type);
  ~CreateAction() override = default;
};

#endif  //R_TYPE_CLIENT_CREATEACTION_HPP
