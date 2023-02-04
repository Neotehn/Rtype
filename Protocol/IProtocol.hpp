#ifndef PROTOCOL_IPROTOCOL_HPP_
#define PROTOCOL_IPROTOCOL_HPP_

#include <memory>
#include <string>

#include "../Client/src/Action/IAction.hpp"
#include "../Client/src/Action/CollisionAction.hpp"
#include "../Client/src/Action/CreateAction.hpp"
#include "../Client/src/Action/IncreaseAction.hpp"
#include "../Client/src/Action/MovementAction.hpp"
#include "../Client/src/Action/ShootAction.hpp"
#include "../Client/src/Action/StateAction.hpp"

class IProtocol {
 public:
  IProtocol() = default;
  virtual ~IProtocol() = default;
  IAction getAction(std::string command);

 private:
  CreateAction getCreateAction(std::string command, int action_id, EntityID id);
  IncreaseAction getIncreaseAction(std::string command, int action_id,
                                   EntityID id);
};

#endif /* !PROTOCOL_IPROTOCOL_HPP_ */
