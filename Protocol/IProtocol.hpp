#ifndef PROTOCOL_IPROTOCOL_HPP_
#define PROTOCOL_IPROTOCOL_HPP_

#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <boost/algorithm/string/find.hpp>
#include <boost/algorithm/string.hpp>

#include "../Client/src/Action/Action.hpp"
#include "../Client/src/Action/CollisionAction.hpp"
#include "../Client/src/Action/CreateAction.hpp"
#include "../Client/src/Action/IncreaseAction.hpp"
#include "../Client/src/Action/MovementAction.hpp"
#include "../Client/src/Action/ShootAction.hpp"
#include "../Client/src/Action/StateAction.hpp"
#include "../Client/src/Action/PosAction.hpp"
#include "../Client/src/Action/VoidAction.hpp"
#include "../Client/src/Action/DestroyAction.hpp"

class IProtocol {
 public:
  IProtocol() = default;
  virtual ~IProtocol() = default;
  std::shared_ptr<Action> getAction(std::string command);

 private:
  std::shared_ptr<Action> getCreateAction(std::vector<std::string> commands,
                                          int action_id, EntityID id);
  std::shared_ptr<Action> getIncreaseAction(std::vector<std::string> commands,
                                            int action_id, EntityID id);
};

#endif /* !PROTOCOL_IPROTOCOL_HPP_ */
