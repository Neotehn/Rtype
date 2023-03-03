#include "./GameState.hpp"

void GameState::initClientLoad() {
  float size_x = m_window->getSize().x;
  float size_y = m_window->getSize().y;
  m_bg_t = m_graphic_loader->loadTexture();
  m_bg_s = m_graphic_loader->loadSprite();
  if (!m_bg_t->loadFromFile("./assets/menubg.jpg")) {
    throw std::runtime_error("Unable to load image.");
  }
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
  m_title->setString("LOADING...");
  m_title->setCharacterSize(50);
  m_title->setPosition({(size_x / 2) - (m_title->getLocalBounds().width / 2),
                        (size_y / 2) - (m_title->getLocalBounds().height / 2)});
}

GameState::GameState(StateMachine &t_machine, rtype::IRenderWindow *t_window,
                     MusicPlayer &t_music_player, std::size_t t_flag,
                     rtype::IGraphicLoader *t_graphic_loader, int *t_level,
                     const std::string& t_path_to_sprite,
                     const std::string& t_player_name,
                     const bool t_replace, std::string t_ip,
                     UdpClient *t_clientCom)
    : State{t_machine, t_window,  t_music_player, t_graphic_loader,
            t_level, t_path_to_sprite, t_player_name, t_replace, t_ip, t_clientCom},
      m_client_input_manager(t_level), m_input_manager(t_level) {
  m_is_running = true;
  m_graphic_loader = t_graphic_loader;
  m_music = m_graphic_loader->loadMusic();
  m_em = std::make_shared<EntityManager>();
  m_player_name = t_player_name;
  if (t_path_to_sprite.empty())
    m_path_to_sprite = "../Client/sprites/starship.png";
  else
    m_path_to_sprite = t_path_to_sprite;
  if (t_flag == client) {
    initClientLoad();
    m_flag = CommunicationFlag::client;
    m_clientCom->setClientInputManager(&m_client_input_manager);
    m_clientCom->setInputManager(&m_input_manager);
    //client creation
  } else {
    m_flag = CommunicationFlag::server;

    m_serverCom =
      new UdpServer(m_io_service, m_input_manager, m_is_running, m_ip);
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
    systems.push_back(std::make_shared<DamageSystem>(
      m_em, m_input_manager, m_clientCom->getPortNumber(), m_is_running,
      m_sounds, m_graphic_loader));
    systems.push_back(
      std::make_shared<CreateObjectSystem>(m_em, m_sounds, m_graphic_loader, m_path_to_sprite));
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
    if (total_coins < 40) return;
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
    while (  // if wanted to revert to original remove everything except l.112 - 115
      m_flag == CommunicationFlag::client &&
      m_clientCom->m_flag != m_clientCom->connected && m_is_running) {
      std::cout << "Connecting to Server ..." << std::endl;
      boost::this_thread::sleep_for(boost::chrono::milliseconds(3000));
      StateAction start_action =
        StateAction(Action::ActionType::START, m_clientCom->getPortNumber());
      m_clientCom->sendMessage(start_action.getCommand());
      std::cout << "waiting on Server Connection" << std::endl;
      m_window->clear();
      m_window->draw(m_bg_s);
      m_window->draw(m_title);
      m_window->display();
    }
    rtype::Event event;
    if (m_window->isOpen()) {
      while (m_window->pollEvent(event)) {
        if (event.type == rtype::EventType::Closed) {
          m_is_running = false;
          std::cout << "yes close pls" << std::endl;
        }
        if (m_flag == CommunicationFlag::client) {
          m_client_input_manager.recordInputs(event, m_mouse, m_window);
        }
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