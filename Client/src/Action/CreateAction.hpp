#ifndef R_TYPE_CLIENT_CREATEACTION_HPP
#define R_TYPE_CLIENT_CREATEACTION_HPP

#include <string>

#include <SFML/System/Vector2.hpp>

#include "IAction.hpp"

class CreateAction : public IAction {
 public:
  enum ObjectType { PLAYER, ENEMY, BULLET };
  CreateAction(EntityID t_id, ObjectType t_object_type, sf::Vector2f t_position,
               std::string t_sprite_path);
  CreateAction(EntityID t_id, ObjectType t_object_type, sf::Vector2f t_position,
               std::string t_sprite_path, int t_action_id);
  ~CreateAction() override = default;

  std::string getCommand() const override;

  ObjectType getObjectType() const;
  sf::Vector2f getPosition() const;
  std::string getSpritePath() const;

 private:
  ObjectType m_object_type;
  sf::Vector2f m_position;
  std::string m_sprite_path;
};

#endif  //R_TYPE_CLIENT_CREATEACTION_HPP
