/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** GameState
*/

#include "../inc/GameState.hpp"

GameState::GameState(StateMachine &t_machine, sf::RenderWindow &t_window,
                     MusicPlayer &t_music_player, std::size_t t_flag,
                     const bool t_replace)
    : State{t_machine, t_window, t_music_player, t_replace} {
  m_is_running = true;
  if (t_flag == client) {
    m_flag = CommunicationFlag::client;
    m_port_number = rand() % 15000 + 40001;

    m_clientCom =
      new UdpClient(m_io_service, "localhost", "50000", m_port_number,
                    m_input_manager, m_client_input_manager);
  } else {
    m_flag = CommunicationFlag::server;

    m_serverCom = new UdpServer(m_io_service, m_input_manager, m_is_running);
  }
  m_music_player.play(MusicID::MISSIONTHEME);
  std::shared_ptr<EntityManager> entity_manager =
    std::make_shared<EntityManager>(initEntityManager());
  //   std::vector<std::shared_ptr<ISystem>> systems = initSystems(entity_manager);
  m_systems = initSystems(entity_manager);
}

GameState::~GameState() {
  if (m_flag == CommunicationFlag::server) {
    delete m_serverCom;
  } else {
    delete m_clientCom;
  }
}

void GameState::pause() { std::cout << "GameState Pause\n"; }

void GameState::resume() { std::cout << "GameState Resume\n"; }

EntityManager GameState::initEntityManager() {
  EntityManager entity_manager;
  initBackground(entity_manager);
  initPlayer(entity_manager, m_serverCom);
  return entity_manager;
}

std::vector<std::shared_ptr<ISystem>>
GameState::initSystems(std::shared_ptr<EntityManager> entity_manager) {
  std::vector<std::shared_ptr<ISystem>> systems;

  if (m_flag == CommunicationFlag::server) {
    systems.push_back(std::make_shared<RandomEnemyGeneratorSystem>(
      entity_manager, m_serverCom));
    systems.push_back(
      std::make_shared<CollisionSystem>(entity_manager, m_serverCom));
    systems.push_back(
      std::make_shared<ShootingSystem>(entity_manager, m_serverCom));
    systems.push_back(
      std::make_shared<MovementSystem>(entity_manager, m_serverCom));
  } else if (m_flag == CommunicationFlag::client) {
    systems.push_back(
      std::make_shared<AnimationSystem>(entity_manager, m_input_manager));
    systems.push_back(
      std::make_shared<CreateObjectSystem>(entity_manager, m_sounds));
    systems.push_back(
      std::make_shared<MovementSystem>(entity_manager, nullptr));
  }
  systems.push_back(std::make_shared<DisplaySystem>(entity_manager, m_window));
  systems.push_back(std::make_shared<DestroySystem>(entity_manager));
  return systems;
}

void GameState::update() {
  while (m_flag == CommunicationFlag::server &&
         m_serverCom->m_flag != m_serverCom->single) {
    std::cout << "waiting on Client Connection" << std::endl;
    boost::this_thread::sleep_for(boost::chrono::milliseconds(3000));
  }
  while (m_flag == CommunicationFlag::client &&
         m_clientCom->m_flag != m_clientCom->connected) {
    std::cout << "Connecting to Server ..." << std::endl;
    boost::this_thread::sleep_for(boost::chrono::milliseconds(3000));
    StateAction start_action =
      StateAction(Action::ActionType::START, m_port_number);
    m_clientCom->sendMessage(start_action.getCommand());
    std::cout << "waiting on Server Connection" << std::endl;
  }
  sf::Event event;
  while (m_window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      m_state_machine.quit();
      std::cout << "yes close pls" << std::endl;
    }
    if (event.type == sf::Event::KeyPressed)
      if (event.key.code == sf::Keyboard::Escape)
        m_next = StateMachine::build<MainState>(m_state_machine, m_window,
                                                m_music_player, true);
    if (m_flag == CommunicationFlag::client)
      m_input_manager.recordInputs(event);
  }
  EventQueue eq = m_input_manager.getInputs();
  SystemData data = {.event_queue = eq};
  if (m_flag == CommunicationFlag::client && m_clientCom->m_flag) {
    for (std::shared_ptr<Action> action : eq.getEventQueue()) {
      Action::ActionType type = action->getType();
      if ((type == Action::ActionType::UP || type == Action::ActionType::DOWN ||
           type == Action::ActionType::LEFT ||
           type == Action::ActionType::RIGHT ||
           type == Action::ActionType::SHOOT) &&
          action.get()->isTriggeredByUser())
        m_clientCom->sendMessage(action->getCommand());
    }
  }
  if (m_flag == CommunicationFlag::server && m_serverCom->m_flag) {
    m_serverCom->sendEvents();
  }
  for (std::shared_ptr<ISystem> system : m_systems) {
    system->updateData(data);
    system->update();
  }
}

void GameState::draw() {}