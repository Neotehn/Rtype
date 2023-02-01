#ifndef R_TYPE_CLIENT_INCREASEACTION_HPP
#define R_TYPE_CLIENT_INCREASEACTION_HPP

#include "IAction.hpp"

class IncreaseAction : public IAction {
  public:
    enum IncreaseType {
        SPEED,
        FIRE_RATE,
        DAMAGE,
        LIFE,
        SHIELD,
        BOMB
    };
    IncreaseAction(EntityID t_id, IncreaseType t_type, int t_value);
    ~IncreaseAction() override = default;

    std::string getCommand() const override;

    IncreaseType getIncreaseType() const;
    int getValue() const;

  private:
    IncreaseType m_type;
    int m_value;
};

#endif  //R_TYPE_CLIENT_INCREASEACTION_HPP
