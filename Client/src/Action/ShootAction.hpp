#ifndef R_TYPE_CLIENT_SHOOTACTION_HPP
#define R_TYPE_CLIENT_SHOOTACTION_HPP

#include "IAction.hpp"

class ShootAction : public IAction {
  public:
    ShootAction(EntityID t_id, int t_damage, int t_type);
    ~ShootAction() override = default;

    std::string getCommand() const override;

    int getDamage() const;
    int getShootType() const;

  private:
    int m_damage;
    int m_type;
};

#endif  //R_TYPE_CLIENT_SHOOTACTION_HPP
