#include "../inc/PlayState.hpp"

int counter;

EntityManager init() {
  EntityManager entity_manager;

  // background layer 1
  EntityID background1 = entity_manager.createNewEntity();
  entity_manager.Assign<int>(background1, (-272 * 5));
  entity_manager.Assign<float>(background1, 1);
  entity_manager.Assign<sf::Vector2f>(background1, sf::Vector2f(0, 0));
  entity_manager.Assign<SpriteECS>(
    background1, SpriteECS("./sprites/background/bg1.png", {5, 5}));

  // background layer 2
  EntityID background2 = entity_manager.createNewEntity();
  entity_manager.Assign<int>(background2, (-272 * 10));
  entity_manager.Assign<float>(background2, 2);
  entity_manager.Assign<sf::Vector2f>(background2, sf::Vector2f(0, 160));
  entity_manager.Assign<SpriteECS>(
    background2, SpriteECS("./sprites/background/bg2.png", {4, 4}));

  // background layer 3
  EntityID background3 = entity_manager.createNewEntity();
  entity_manager.Assign<int>(background3, (-272 * 5));
  entity_manager.Assign<float>(background3, 3);
  entity_manager.Assign<sf::Vector2f>(background3, sf::Vector2f(0, 0));
  entity_manager.Assign<SpriteECS>(
    background3, SpriteECS("./sprites/background/bg3.png", {5, 5}));

  // player
  EntityID player = entity_manager.createNewEntity();
  SpriteECS player_sprite = SpriteECS("./sprites/starship.png");

  float *player_speed = entity_manager.Assign<float>(player, float(10));
  Pos *player_pos = entity_manager.Assign<Pos>(
    player, Pos{sf::Vector2f(0, 0), sf::Vector2f(300, 300)});

  sf::RectangleShape body;
  body.setSize({200, 200});
  body.setPosition(player_pos->position);
  body.setTexture(player_sprite.getTexture());
  body.setRotation(90.0);
  body.setOutlineColor(sf::Color::Red);
  // body.setOutlineThickness(5);
  sf::RectangleShape *player_body =
    entity_manager.Assign<sf::RectangleShape>(player, body);
  return entity_manager;
}

PlayState::PlayState(StateMachine &machine, sf::RenderWindow &window,
                     const bool replace)
    : State{machine, window, replace}, m_input_manager{} {
  if (!m_backgroundTexture.loadFromFile("./assets/play.jpg")) {
    throw std::runtime_error{"Was unable to load image 'img/play.png'"};
  }
  float scale_x = 1280.0 / m_backgroundTexture.getSize().x;
  float scale_y = 720.0 / m_backgroundTexture.getSize().y;
  m_background.setTexture(m_backgroundTexture, true);
  m_background.setScale(scale_x, scale_y);

  m_entity_manager = init();
  m_entity_manager_ptr = std::make_shared<EntityManager>(m_entity_manager);
  m_systems.push_back(
    std::make_shared<DisplaySystem>(m_entity_manager_ptr, window));
  m_systems.push_back(std::make_shared<MovementSystem>(m_entity_manager_ptr));
  m_systems.push_back(std::make_shared<ShootingSystem>(m_entity_manager_ptr));
  m_systems.push_back(
    std::make_shared<RandomEnemyGeneratorSystem>(m_entity_manager_ptr));
  m_systems.push_back(std::make_shared<CollisionSystem>(m_entity_manager_ptr));
  m_systems.push_back(std::make_shared<AnimationSystem>(m_entity_manager_ptr));

  std::cout << "PlayState Init\n";
}

void PlayState::pause() { std::cout << "PlayState Pause\n"; }

void PlayState::resume() { std::cout << "PlayState Resume\n"; }

void PlayState::update() {
  sf::Event event;
  while (m_window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) m_state_machine.quit();
    if (event.type == sf::Event::KeyPressed)
      if (event.key.code == sf::Keyboard::Escape)
        m_next =
          StateMachine::build<MainState>(m_state_machine, m_window, true);
    m_input_manager.recordInputs(event);
  }
}

void PlayState::draw() {
  SystemData data = {.event_queue = m_input_manager.getInputs()};
  for (std::shared_ptr<ISystem> system : m_systems) {
    system->updateData(data);
    system->update();
  }
}