#include "Game.hpp"

Game::Game(std::size_t t_flag)
    : m_window(sf::VideoMode(800, 800), "R-Type Epitech") {
  m_window.setFramerateLimit(60);

  if (t_flag == client) {
    m_flag = CommunicationFlag::client;
    std::size_t portNumber = rand() % 15000 + 40001;

    m_clientCom = new UdpClient(m_io_service, "localhost", "50000", portNumber);
  } else {
    m_flag = CommunicationFlag::server;

    m_serverCom = new UdpServer(m_io_service);
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
    sf::Event event;
    while (m_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) m_window.close();
      m_input_manager.recordInputs(event);
    }
    SystemData data = {.event_queue = m_input_manager.getInputs()};
    if (m_flag == CommunicationFlag::client) {
      m_clientCom->sendMessage("yes");
    }
    if (m_flag == CommunicationFlag::server && m_serverCom->m_flag) {
      m_serverCom->sendMessage("yes");
    }
    for (std::shared_ptr<ISystem> system : systems) {
      system->updateData(data);
      system->update();
    }
  }
}
