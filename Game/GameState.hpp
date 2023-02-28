#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <memory>
#include <string>
#include <vector>

#include "../Client/src/Action/Action.hpp"
#include "../Client/src/InputManager/InputManager.hpp"
#include "../Client/Protocol/UdpClient.hpp"
#include "CreateEntities/Init.hpp"
#include "ECS/EntityManager.hpp"
#include "ECS/DataTypesECS.hpp"
#include "ECS/ISystem.hpp"
#include "Systems/AnimationSystem.hpp"
#include "Systems/CollisionSystem.hpp"
#include "Systems/CreateObjectSystem.hpp"
#include "Systems/CreatePlayerSystem.hpp"
#include "Systems/DisplaySystem.hpp"
#include "Systems/DestroySystem.hpp"
#include "Systems/MovementSystem.hpp"
#include "Systems/DamageSystem.hpp"
#include "Systems/RandomEnemyGeneratorSystem.hpp"
#include "Systems/ShootingSystem.hpp"
#include "Systems/PowerUpSystem.hpp"
#include "../Server/Protocol/UdpServer.hpp"
#include "../Server/Protocol/UdpSession.hpp"
#include "CreateEntities/Init.hpp"

#include "../GameEngine/src/MusicPlayer.hpp"
#include "../GameEngine/src/State.hpp"
#include "../GameEngine/src/StateMachine.hpp"
#include "../GameEngine/src/States/MainState.hpp"

class StateMachine;

class GameState final : public State {
 public:
  GameState(StateMachine &t_machine, rtype::IRenderWindow *t_window,
            MusicPlayer &t_music_player, std::size_t t_flag,
            rtype::IGraphicLoader *t_graphic_loader, int *t_level,
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
  rtype::IMusic *m_music;
  std::shared_ptr<EntityManager> m_em;
  std::vector<SoundSystem::SoundType> m_sounds;

  std::vector<std::shared_ptr<ISystem>> initSystems();

  rtype::ITexture *m_bg_t;
  rtype::ISprite *m_bg_s;
  rtype::IFont *m_font;
  rtype::IText *m_title;
};

#endif /* !GAMESTATE_HPP_ */
