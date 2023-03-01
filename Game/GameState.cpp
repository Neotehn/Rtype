#include "./GameState.hpp"

GameState::GameState(StateMachine &t_machine, rtype::IRenderWindow *t_window,
                     MusicPlayer &t_music_player, std::size_t t_flag,
                     rtype::IGraphicLoader *t_graphic_loader, int *t_level,
                     const bool t_replace)
    : State{t_machine,        t_window, t_music_player,
            t_graphic_loader, t_level,  t_replace},
      m_client_input_manager(t_level), m_input_manager(t_level) {
  m_is_running = true;
  m_graphic_loader = t_graphic_loader;
  m_music = m_graphic_loader->loadMusic();
  m_em = std::make_shared<EntityManager>();
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
  loadLevel(m_level, m_em, m_graphic_loader, m_music,
            m_flag == CommunicationFlag::client);
  m_systems = initSystems();
}

GameState::~GameState() {
  if (m_flag == CommunicationFlag::server) {
    delete m_serverCom;
  } else {
    delete m_clientCom;
  }
  if (m_music) { delete m_music; }
}

std::vector<std::shared_ptr<ISystem>> GameState::initSystems() {
  std::vector<std::shared_ptr<ISystem>> systems;

  if (m_flag == CommunicationFlag::server) {
    systems.push_back(std::make_shared<CreatePlayerSystem>(m_em, m_serverCom,
                                                           m_graphic_loader));
    systems.push_back(std::make_shared<RandomEnemyGeneratorSystem>(
      m_em, m_serverCom, m_graphic_loader));
    systems.push_back(
      std::make_shared<CollisionSystem>(m_em, m_serverCom, m_graphic_loader));
    systems.push_back(
      std::make_shared<ShootingSystem>(m_em, m_serverCom, m_graphic_loader));
    systems.push_back(std::make_shared<MovementSystem>(m_em, m_serverCom));
  } else {
    systems.push_back(
      std::make_shared<DamageSystem>(m_em, m_input_manager, m_port_number,
                                     m_is_running, m_sounds, m_graphic_loader));
    systems.push_back(
      std::make_shared<CreateObjectSystem>(m_em, m_sounds, m_graphic_loader));
    systems.push_back(
      std::make_shared<MovementSystem>(m_em, nullptr, m_clientCom));
    systems.push_back(std::make_shared<AnimationSystem>(m_em, m_input_manager));
    systems.push_back(
      std::make_shared<PowerUpSystem>(m_em, m_sounds, m_graphic_loader));
    systems.push_back(
      std::make_shared<SoundSystem>(m_em, m_sounds, m_graphic_loader));
  }
  systems.push_back(std::make_shared<DisplaySystem>(m_em, m_window));
  systems.push_back(std::make_shared<DestroySystem>(m_em));
  return systems;
}

void GameState::pause() { std::cout << "GameState Pause\n"; }

void GameState::resume() { std::cout << "GameState Resume\n"; }

void GameState::manageLevels() {
  if (*m_level == 2) {
    if (m_flag == CommunicationFlag::server && m_will_reload) {
      m_will_reload = false;
      *m_level += 1;
      m_level_two_enemy_created = false;
      loadLevel(m_level, m_em, m_graphic_loader, m_music,
                (m_flag == CommunicationFlag::client), m_serverCom);
      std::cout << "finished level 2" << std::endl;
      return;
    }
    if (!m_level_two_enemy_created) {
      for (EntityID ent : EntityViewer<Enemy>(*m_em)) {
        Enemy *enem = (*m_em).Get<Enemy>(ent);
        if (enem->obj->type == "paywall") {
          m_level_two_enemy_created = true;
          break;
        }
      }
    }
    if (!m_level_two_enemy_created) return;
    bool paywall_exists = false;
    for (EntityID ent : EntityViewer<Enemy>(*m_em)) {
      Enemy *enem = (*m_em).Get<Enemy>(ent);
      if (enem->obj->type == "paywall") {
        paywall_exists = true;
        break;
      }
    }
    if (paywall_exists) return;
    if (m_flag == CommunicationFlag::server) {
      m_will_reload = true;
    } else {
      *m_level += 1;
      m_level_two_enemy_created = false;
      loadLevel(m_level, m_em, m_graphic_loader, m_music,
                (m_flag == CommunicationFlag::client), m_serverCom);
      std::cout << "finished level 2" << std::endl;
    }
  } else if (*m_level == 1) {
    if (m_flag == CommunicationFlag::server && m_will_reload) {
      m_will_reload = false;
      *m_level += 1;
      loadLevel(m_level, m_em, m_graphic_loader, m_music,
                (m_flag == CommunicationFlag::client), m_serverCom);
      std::cout << "finished level 1" << std::endl;
      return;
    }
    int total_coins = 0;
    for (EntityID ent : EntityViewer<Player>(*m_em)) {
      Player *player = (*m_em).Get<Player>(ent);
      total_coins += player->coins;
    }
    if (total_coins < 400) return;
    if (m_flag == CommunicationFlag::server) {
      m_will_reload = true;
    } else {
      *m_level += 1;

      loadLevel(m_level, m_em, m_graphic_loader, m_music,
                (m_flag == CommunicationFlag::client), m_serverCom);
      std::cout << "finished level 1" << std::endl;
    }
  }
}

void GameState::update() {
  while (m_is_running) {
    while (m_flag == CommunicationFlag::server &&
           m_serverCom->m_flag != m_serverCom->coop) {
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
    rtype::Event event;
    if (m_window->isOpen()) {
      while (m_window->pollEvent(event)) {
        if (event.type == rtype::EventType::Closed) {
          m_is_running = false;
          std::cout << "yes close pls" << std::endl;
        }
        if (m_flag == CommunicationFlag::client)
          m_client_input_manager.recordInputs(event);
      }
    }
    EventQueue eq = m_input_manager.getInputsWithoutPop();
    for (std::shared_ptr<Action> action : eq.getEventQueue()) {
      Action::ActionType type = action->getType();
      if (type == Action::ActionType::RESTART && !action->isTriggeredByUser()) {
        *m_level = action->getId();
        loadLevel(m_level, m_em, m_graphic_loader, m_music,
                  (m_flag == CommunicationFlag::client), m_serverCom);
      }
    }
    manageLevels();
    SystemData data = {.event_queue = m_input_manager.getInputs()};
    if (m_flag == CommunicationFlag::client && m_clientCom->m_flag) {
      EventQueue eq = m_client_input_manager.getInputsWithoutPop();
      for (std::shared_ptr<Action> action : eq.getEventQueue()) {
        Action::ActionType type = action->getType();
        if ((type == Action::ActionType::RESTART ||
             type == Action::ActionType::SHOOT) &&
            action->isTriggeredByUser()) {
          m_client_input_manager.removeEvent(action->getActionId());
        }
        if ((type == Action::ActionType::RESTART ||
             type == Action::ActionType::UP ||
             type == Action::ActionType::DOWN ||
             type == Action::ActionType::LEFT ||
             type == Action::ActionType::RIGHT ||
             type == Action::ActionType::SHOOT) &&
            action->isTriggeredByUser())
          m_clientCom->sendMessage(action->getCommand());
      }
    }
    if (m_flag == CommunicationFlag::server && m_serverCom->m_flag == 2) {
      m_serverCom->sendEvents();
    }
    for (std::shared_ptr<ISystem> system : m_systems) {
      system->updateData(data);
      system->update();
    }
  }
  if (m_window->isOpen()) { m_window->close(); }
  if (m_flag == CommunicationFlag::client) {
    std::cout << "Stop connection to Server ..." << std::endl;
    StateAction start_action =
      StateAction(Action::ActionType::END, m_port_number);
    m_clientCom->sendMessage(start_action.getCommand());
  }
  m_music->stop();
  m_state_machine.quit();
}

void GameState::draw() {}