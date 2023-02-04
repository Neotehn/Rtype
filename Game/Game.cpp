#include "Game.hpp"

Game::Game(std::size_t t_flag)
    : m_window(sf::VideoMode(800, 800), "R-Type Epitech") {
  m_window.setFramerateLimit(60);

  if (t_flag == client) {
    m_flag = CommunicationFlag::client;
    m_port_number = rand() % 15000 + 40001;

    m_clientCom = new UdpClient(m_io_service, "localhost", "50000",
                                m_port_number, m_input_manager);
  } else {
    m_flag = CommunicationFlag::server;

    m_serverCom = new UdpServer(m_io_service, m_input_manager);
  }
}

Game::~Game() {
  if (m_flag == CommunicationFlag::server) {
    delete m_serverCom;
  } else {
    delete m_clientCom;
  }
}

EntityManager Game::initEntityManager() {
  EntityManager entity_manager;
  initBackground(entity_manager);
  initPlayer(entity_manager);
  return entity_manager;
}

std::vector<std::shared_ptr<ISystem>>
Game::initSystems(std::shared_ptr<EntityManager> entity_manager) {
  std::vector<std::shared_ptr<ISystem>> systems;

  systems.push_back(std::make_shared<DisplaySystem>(entity_manager, m_window));
  systems.push_back(std::make_shared<MovementSystem>(entity_manager));
  systems.push_back(std::make_shared<ShootingSystem>(entity_manager));
  systems.push_back(
    std::make_shared<RandomEnemyGeneratorSystem>(entity_manager));
  systems.push_back(std::make_shared<CollisionSystem>(entity_manager));
  systems.push_back(std::make_shared<AnimationSystem>(entity_manager));

  return systems;
}

void Game::run() {
  std::shared_ptr<EntityManager> entity_manager =
    std::make_shared<EntityManager>(initEntityManager());
  std::vector<std::shared_ptr<ISystem>> systems = initSystems(entity_manager);

  std::cout << "running " << m_flag << std::endl;
  while (m_window.isOpen()) {
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
        StateAction(IAction::ActionType::START, m_port_number);
      m_clientCom->sendMessage(start_action.getCommand());
      std::cout << "waiting on Server Connection" << std::endl;
    }
    sf::Event event;
    while (m_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        m_window.close();
        std::cout << "yes close pls" << std::endl;
      }
      m_input_manager.recordInputs(event);
    }
    EventQueue eq = m_input_manager.getInputs();
    SystemData data = {.event_queue = eq};
    if (m_flag == CommunicationFlag::client && m_clientCom->m_flag) {
      if (!eq.getEventQueue().empty()) {
        std::cout << "length queue: "
                  << std::to_string(eq.getEventQueue().size()) << std::endl;
      }
      for (std::shared_ptr<IAction> action : eq.getEventQueue()) {
        IAction::ActionType type = action.get()->getType();
        std::string command;
        std::cout << "action type " << type << std::endl;
        switch (type) {
          case IAction::ActionType::START:
          case IAction::ActionType::DEAD:
          case IAction::ActionType::END:
            command = (dynamic_cast<StateAction *>(action.get()))->getCommand();
            break;
          case IAction::ActionType::UP:
          case IAction::ActionType::DOWN:
          case IAction::ActionType::LEFT:
          case IAction::ActionType::RIGHT:
            command =
              (dynamic_cast<MovementAction *>(action.get()))->getCommand();
            break;
          case IAction::ActionType::SHOOT:
            command = (dynamic_cast<ShootAction *>(action.get()))->getCommand();
            break;
          case IAction::ActionType::CREATE:
            command =
              (dynamic_cast<CreateAction *>(action.get()))->getCommand();
            break;
          case IAction::ActionType::INCREASE:
            command =
              (dynamic_cast<IncreaseAction *>(action.get()))->getCommand();
            break;
          case IAction::ActionType::COLLISION:
            command =
              (dynamic_cast<CollisionAction *>(action.get()))->getCommand();
            break;
        }
        m_clientCom->sendMessage(command);
      }
    }
    if (m_flag == CommunicationFlag::server && m_serverCom->m_flag) {}
    for (std::shared_ptr<ISystem> system : systems) {
      system->updateData(data);
      system->update();
    }
  }
}
