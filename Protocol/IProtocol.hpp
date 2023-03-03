#ifndef PROTOCOL_IPROTOCOL_HPP_
#define PROTOCOL_IPROTOCOL_HPP_

#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <boost/algorithm/string/find.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include "../Client/src/Action/Action.hpp"
#include "../Client/src/Action/CollisionAction.hpp"
#include "../Client/src/Action/CreateAction.hpp"
#include "../Client/src/Action/DamageAction.hpp"
#include "../Client/src/Action/DestroyAction.hpp"
#include "../Client/src/Action/IncreaseAction.hpp"
#include "../Client/src/Action/MovementAction.hpp"
#include "../Client/src/Action/ShootAction.hpp"
#include "../Client/src/Action/StateAction.hpp"
#include "../Client/src/Action/PosAction.hpp"
#include "../Client/src/Action/VoidAction.hpp"
#include "../Client/src/Action/LeaveLobbyAction.hpp"
#include "../Client/src/Action/JoinLobbyAction.hpp"
#include "../Client/src/Action/CreateLobbyAction.hpp"
#include "../Client/src/Action/JoinSuccessfullAction.hpp"
#include "../Client/src/Action/ChadAction.hpp"

struct Lobby {
  std::string m_lobby_code;
  std::size_t m_player_count;
  std::vector<std::string> m_player_names;
  std::vector<boost::asio::ip::udp::endpoint> m_endpoints;
};

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
