#ifndef GAME_GAME_HPP
#define GAME_GAME_HPP

#include <memory>
#include <string>
#include <vector>

#include "./ECS/EntityManager.hpp"
#include "./ECS/DataTypesECS.hpp"
#include "./ECS/ISystem.hpp"

#include "./Encapsulation/Networking/Boost/MethodEncaps.hpp"
#include "./Encapsulation/IRenderWindow.hpp"
#include "./Encapsulation/SFML/RenderWindow.hpp"

#include "./Systems/AnimationSystem.hpp"
#include "./Systems/CollisionSystem.hpp"
#include "./Systems/CreateObjectSystem.hpp"
#include "./Systems/DisplaySystem.hpp"
#include "./Systems/DestroySystem.hpp"
#include "./Systems/MovementSystem.hpp"
#include "./Systems/DamageSystem.hpp"
#include "./Systems/RandomEnemyGeneratorSystem.hpp"
#include "./Systems/ShootingSystem.hpp"
#include "./Systems/SoundSystem.hpp"
#include "./Systems/PowerUpSystem.hpp"
#include "../Client/src/Action/Action.hpp"
#include "../Client/src/InputManager/InputManager.hpp"
#include "../Client/Protocol/UdpClient.hpp"
#include "../Server/Protocol/UdpServer.hpp"
#include "../Server/Protocol/UdpSession.hpp"
#include "./CreateEntities/Init.hpp"

class Game {
 public:
  Game(std::size_t t_flag, rtype::IIoService &t_io_service);
  ~Game();

  void run();

 private:
  enum CommunicationFlag { server, client };
  bool m_is_running;
  std::size_t m_port_number;
  rtype::IIoService &m_io_service;
  rtype::IRenderWindow *m_window;
  std::vector<SoundSystem::SoundType> m_sounds;
  InputManager m_input_manager;
  InputManager m_client_input_manager;
  CommunicationFlag m_flag;
  UdpClient *m_clientCom = nullptr;
  UdpServer *m_serverCom = nullptr;

  EntityManager initEntityManager();
  std::vector<std::shared_ptr<ISystem>>
    initSystems(std::shared_ptr<EntityManager>);
};

#endif  //GAME_GAME_HPP
