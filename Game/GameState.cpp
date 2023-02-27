#include "./GameState.hpp"

GameState::GameState(StateMachine &t_machine, rtype::IRenderWindow *t_window,
                     MusicPlayer &t_music_player, std::size_t t_flag,
                     rtype::IGraphicLoader *t_graphic_loader,
                     const bool t_replace)
    : State{t_machine, t_window, t_music_player, t_graphic_loader, t_replace},
      m_home_btn(Button(
        "./assets/icons/home.png",
        rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 32),
                        static_cast<float>(m_window->getSize().y - 100)},
        rtype::Vector2f{64, 64}, t_graphic_loader)),
      m_start_btn(Button(
        "./assets/startBtn.png",
        rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 135),
                        static_cast<float>(m_window->getSize().y - 230)},
        rtype::Vector2f{270, 130}, t_graphic_loader)) {
  m_is_running = true;
  m_graphic_loader = t_graphic_loader;
  if (t_flag == client) {
    m_bg_t = m_graphic_loader->loadTexture();
    m_bg_s = m_graphic_loader->loadSprite();
    if (!m_bg_t->loadFromFile("./assets/menubg.jpg")) {
      throw std::runtime_error("Unable to load image.");
    }
    m_player_one_t = m_graphic_loader->loadTexture();
    m_player_one_s = m_graphic_loader->loadSprite();
    if (!m_player_one_t->loadFromFile("./assets/icons/gamepad1.png")) {
      throw std::runtime_error("Unable to load image.");
    }
    m_player_one_s->setTexture(m_player_one_t, true);
    m_player_one_s->setPosition(
      rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 150),
                      static_cast<float>(m_window->getSize().y / 2 - 150)});

    m_player_two_t = m_graphic_loader->loadTexture();
    m_player_two_s = m_graphic_loader->loadSprite();
    if (!m_player_two_t->loadFromFile("./assets/icons/gamepad2.png")) {
      throw std::runtime_error("Unable to load image.");
    }
    m_player_two_s->setTexture(m_player_two_t, true);
    m_player_two_s->setPosition(
      rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 + 50),
                      static_cast<float>(m_window->getSize().y / 2 - 150)});
    float size_x = m_window->getSize().x;
    float size_y = m_window->getSize().y;
    float scale_x = size_x / m_bg_t->getSize().x;
    float scale_y = size_y / m_bg_t->getSize().y;
    m_bg_s->setTexture(m_bg_t, true);
    m_bg_s->setScale({scale_x, scale_y});
    m_font = m_graphic_loader->loadFont();
    if (!m_font->loadFromFile("./assets/font/nasalization-rg.ttf")) {
      throw std::runtime_error("Unable to load font.");
    }
    m_title = m_graphic_loader->loadText();
    m_title->setFont(m_font);
    m_title->setString("LOBBY");
    m_title->setCharacterSize(50);
    m_title->setPosition(
      {(size_x / 2) - (m_title->getLocalBounds().width / 2), 100});
    m_flag = CommunicationFlag::client;
    m_port_number = rand() % 15000 + 40001;

    m_clientCom =
      new UdpClient(m_io_service, "localhost", "50000", m_port_number,
                    m_input_manager, m_client_input_manager);
  } else {
    m_flag = CommunicationFlag::server;

    m_serverCom = new UdpServer(m_io_service, m_input_manager, m_is_running);
  }
  m_music_player.play(MusicID::MISSION_THEME);
  std::shared_ptr<EntityManager> entity_manager =
    std::make_shared<EntityManager>(initEntityManager());
  m_systems = initSystems(entity_manager);
}

GameState::~GameState() {
  if (m_flag == CommunicationFlag::server) {
    delete m_serverCom;
  } else {
    delete m_clientCom;
  }
}

EntityManager GameState::initEntityManager() {
  EntityManager entity_manager;
  initBackground(entity_manager, m_graphic_loader);
  return entity_manager;
}

std::vector<std::shared_ptr<ISystem>>
GameState::initSystems(std::shared_ptr<EntityManager> entity_manager) {
  std::vector<std::shared_ptr<ISystem>> systems;

  if (m_flag == CommunicationFlag::server) {
    systems.push_back(std::make_shared<CreatePlayerSystem>(
      entity_manager, m_serverCom, m_graphic_loader));
    systems.push_back(std::make_shared<RandomEnemyGeneratorSystem>(
      entity_manager, m_serverCom, m_graphic_loader));
    systems.push_back(
      std::make_shared<CollisionSystem>(entity_manager, m_serverCom));
    systems.push_back(std::make_shared<ShootingSystem>(
      entity_manager, m_serverCom, m_graphic_loader));
    systems.push_back(
      std::make_shared<MovementSystem>(entity_manager, m_serverCom));
  } else {
    systems.push_back(std::make_shared<DamageSystem>(
      entity_manager, m_input_manager, m_port_number, m_is_running, m_sounds,
      m_graphic_loader));
    systems.push_back(std::make_shared<CreateObjectSystem>(
      entity_manager, m_sounds, m_graphic_loader));
    systems.push_back(
      std::make_shared<MovementSystem>(entity_manager, nullptr, m_clientCom));
    systems.push_back(
      std::make_shared<AnimationSystem>(entity_manager, m_input_manager));
    systems.push_back(std::make_shared<PowerUpSystem>(entity_manager, m_sounds,
                                                      m_graphic_loader));
    systems.push_back(std::make_shared<SoundSystem>(entity_manager, m_sounds,
                                                    m_graphic_loader));
  }
  systems.push_back(std::make_shared<DisplaySystem>(entity_manager, m_window));
  systems.push_back(std::make_shared<DestroySystem>(entity_manager));
  return systems;
}

void GameState::pause() { std::cout << "GameState Pause\n"; }

void GameState::resume() { std::cout << "GameState Resume\n"; }

void GameState::update() {
  while (m_is_running) {
    while (m_flag == CommunicationFlag::server &&
           m_serverCom->m_flag != m_serverCom->coop) {
      std::cout << "waiting on Client Connection" << std::endl;
      boost::this_thread::sleep_for(boost::chrono::milliseconds(3000));
    }
    while (m_flag == CommunicationFlag::client &&
           m_clientCom->m_flag != m_clientCom->connected && m_is_running) {
      rtype::Vector2i mouse_pos = m_mouse->getMousePosition(m_window);
      rtype::Vector2f mouse_pos_f{static_cast<float>(mouse_pos.x),
                                  static_cast<float>(mouse_pos.y)};
      for (auto event1 = rtype::Event{}; m_window->pollEvent(event1);) {
        if (event1.type == rtype::EventType::MouseMoved) {
          m_start_btn.is_hovered(mouse_pos_f);
          m_home_btn.is_hovered(mouse_pos_f);
        }
        if (m_mouse->isLeftMouseButtonPressed()) {
          if (m_home_btn.is_pressed(mouse_pos_f)) {
            std::cout << "Connecting to Server ..." << std::endl;
            boost::this_thread::sleep_for(boost::chrono::milliseconds(3000));
            StateAction connect_action =
              StateAction(Action::ActionType::CONNECT, m_port_number);
            m_clientCom->sendMessage(connect_action.getCommand());
            std::cout << "waiting on Server Connection" << std::endl;
          }
          if (m_start_btn.is_pressed(mouse_pos_f)) {
            std::cout << "Connecting to Server ..." << std::endl;
            boost::this_thread::sleep_for(boost::chrono::milliseconds(3000));
            StateAction start_action =
              StateAction(Action::ActionType::START, m_port_number);
            m_clientCom->sendMessage(start_action.getCommand());
            std::cout << "waiting on Server Connection" << std::endl;
          }
        }
        if (event1.type == rtype::EventType::Closed) { m_is_running = false; }
      }
      std::cout << "my id: " << m_clientCom->m_id << std::endl;
      m_window->clear();
      m_window->draw(m_bg_s);
      m_window->draw(m_title);
      m_window->draw(m_start_btn.getSprite());
      m_window->draw(m_home_btn.getSprite());
      m_window->display();
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
    SystemData data = {.event_queue = m_input_manager.getInputs()};
    if (m_flag == CommunicationFlag::client && m_clientCom->m_flag) {
      EventQueue eq = m_client_input_manager.getInputsWithoutPop();
      for (std::shared_ptr<Action> action : eq.getEventQueue()) {
        Action::ActionType type = action->getType();
        if ((type == Action::ActionType::UP ||
             type == Action::ActionType::DOWN ||
             type == Action::ActionType::LEFT ||
             type == Action::ActionType::RIGHT ||
             type == Action::ActionType::SHOOT) &&
            action.get()->isTriggeredByUser())
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
  m_state_machine.quit();
}

void GameState::draw() {}