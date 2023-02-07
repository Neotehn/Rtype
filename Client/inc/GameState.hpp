/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** GameState
*/

#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <memory>
#include <string>
#include <vector>

#include "../../Game/ECS/EntityManager.hpp"
#include "../../Game/ECS/DataTypesECS.hpp"
#include "../../Game/ECS/ISystem.hpp"
#include "../../Game/Systems/AnimationSystem.hpp"
#include "../../Game/Systems/CollisionSystem.hpp"
#include "../../Game/Systems/CreateObjectSystem.hpp"
#include "../../Game/Systems/DisplaySystem.hpp"
#include "../../Game/Systems/DestroySystem.hpp"
#include "../../Game/Systems/MovementSystem.hpp"
#include "../../Game/Systems/RandomEnemyGeneratorSystem.hpp"
#include "../../Game/Systems/ShootingSystem.hpp"
#include "../src/Action/Action.hpp"
#include "../src/InputManager/InputManager.hpp"
#include "../Protocol/UdpClient.hpp"
#include "../../Server/Protocol/UdpServer.hpp"
#include "../../Server/Protocol/UdpSession.hpp"
#include "../../Game/CreateEntities/Init.hpp"

#include "../../GameEngine/inc/MusicPlayer.hpp"
#include "../../GameEngine/inc/State.hpp"
#include "../../GameEngine/inc/StateMachine.hpp"
#include "../inc/MainState.hpp"
#include "../src/InputManager/InputManager.hpp"

class StateMachine;

class GameState final : public State {
 public:
  GameState(StateMachine &t_machine, sf::RenderWindow &t_window,
            MusicPlayer &t_music_player, std::size_t t_flag,
            bool t_replace = true);
  ~GameState();

  void pause() override;
  void resume() override;

  void update() override;
  void draw() override;

 private:
  enum CommunicationFlag { server, client };
  std::size_t m_port_number;
  boost::asio::io_service m_io_service;
  InputManager m_input_manager;
  InputManager m_client_input_manager;
  CommunicationFlag m_flag;
  UdpClient *m_clientCom = nullptr;
  UdpServer *m_serverCom = nullptr;
  std::vector<std::shared_ptr<ISystem>> m_systems;
  bool m_is_running;

  EntityManager initEntityManager();
  std::vector<std::shared_ptr<ISystem>>
    initSystems(std::shared_ptr<EntityManager>);
};

#endif /* !GAMESTATE_HPP_ */
