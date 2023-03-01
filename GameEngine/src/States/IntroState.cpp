#include "IntroState.hpp"

IntroState::IntroState(StateMachine &t_machine,
                             rtype::IRenderWindow *t_window,
                             MusicPlayer &t_music_player, std::size_t t_flag,
                             rtype::IGraphicLoader *t_graphic_loader,
                             int *t_level, const bool t_replace)
    : State(t_machine, t_window, t_music_player, t_graphic_loader, t_level,
            t_replace),
      m_start_btn(
        Button("./assets/startBtn.png",
               rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 + 135),
                               static_cast<float>(m_window->getSize().y - 180)},
               rtype::Vector2f{270, 130}, t_graphic_loader)),
      m_flag(t_flag) {
  m_bg_t = m_graphic_loader->loadTexture();
  m_bg_s = m_graphic_loader->loadSprite();
  m_spaceship_t = m_graphic_loader->loadTexture();
  m_spaceship_s = m_graphic_loader->loadSprite();
  m_spaceMovement = {0.5, 1};
  if (!m_spaceship_t->loadFromFile("./sprites/starship.png")) {
    throw std::runtime_error("Unable to load image.");
  }
  if (!m_bg_t->loadFromFile("./assets/menubg.jpg")) {
    throw std::runtime_error("Unable to load image.");
  }
  float size_x = m_window->getSize().x;
  float size_y = m_window->getSize().y;
  float scale_x = size_x / m_bg_t->getSize().x;
  float scale_y = size_y / m_bg_t->getSize().y;
  m_bg_s->setTexture(m_bg_t, true);
  m_bg_s->setScale({scale_x, scale_y});


  m_spaceship_s->setScale({0.2, 0.2});
  m_spaceship_s->rotate(90);
  m_spaceship_s->setOrigin({static_cast<float>(m_spaceship_t->getSize().x / 2),
                            static_cast<float>(m_spaceship_t->getSize().y / 2)});

  m_spaceship_s->setPosition({size_x / 2 - 100, size_y / 2 - 100});
  m_spaceship_s->setTexture(m_spaceship_t, true);
  m_music_player.play(MusicID::MENU_THEME);
}

IntroState::~IntroState() {
  delete m_bg_t;
  delete m_bg_s;
  delete m_spaceship_t;
}

void IntroState::pause() { std::cout << "MenuState Pause\n"; }

void IntroState::resume() { std::cout << "MenuState resume\n"; }

void IntroState::update() {
  animateAndMoveShip();
  for (auto event = rtype::Event{}; m_window->pollEvent(event);) {
    rtype::Vector2i mouse_pos = m_mouse->getMousePosition(m_window);
    rtype::Vector2f mouse_pos_f{static_cast<float>(mouse_pos.x),
                                static_cast<float>(mouse_pos.y)};
    if (event.type == rtype::EventType::MouseMoved) {
      m_start_btn.is_hovered(mouse_pos_f);
    }
    if (m_mouse->isLeftMouseButtonPressed()) {
      if (m_start_btn.is_pressed(mouse_pos_f)) {
        std::cout << "startbtn pressed" << std::endl;
        m_next = StateMachine::build<MainState>(
          m_state_machine, m_window, m_music_player, m_flag, m_graphic_loader,
          m_level, true);
      }
    }
    switch (event.type) {
      case rtype::EventType::Closed:
        m_state_machine.quit();
        break;
      case rtype::EventType::KeyPressed:
        switch (event.key) {
          case rtype::EventKey::Space:
            m_next = StateMachine::build<MainState>(
              m_state_machine, m_window, m_music_player, m_flag,
              m_graphic_loader, m_level, true);
            break;
          case rtype::EventKey::Escape:
            m_state_machine.quit();
            break;
          default:
            break;
        }
        break;
      default:
        break;
    }
  }
}

void IntroState::draw() {
  m_window->clear();
  m_window->draw(m_start_btn.getSprite());
  m_window->draw(m_spaceship_s);
  m_window->display();
}

void IntroState::checkCollisionAngle(rtype::Vector2f collisionNormal) {
  rtype::Vector2f velocity = m_spaceMovement;
  float magnitude = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
  velocity.x /= magnitude;
  velocity.y /= magnitude;

  float dotProduct = velocity.x * collisionNormal.x + velocity.y * collisionNormal.y;
  float angle = std::acos(dotProduct) * 180.0f / M_PI;
}

void IntroState::animateAndMoveShip() {
  const float speed = 1.0f;
  const rtype::FloatRect bounds = m_spaceship_s->getGlobalBounds();
  m_spaceship_s->rotate(1);

  if (bounds.left + bounds.width - 50 >= m_window->getSize().x) {
    m_spaceMovement.x = -speed;
    checkCollisionAngle({-1.0f, 0.0f});
  } else if (bounds.left +50 <= 0) {
    m_spaceMovement.x = speed;
    checkCollisionAngle({1.0f, 0.0f});
  }
  if (bounds.top + bounds.height - 50 >= m_window->getSize().y) {
    m_spaceMovement.y = -speed;
    checkCollisionAngle({0.0f, -1.0f});
  } else if (bounds.top + 50 <= 0) {
    m_spaceMovement.y = speed;
    checkCollisionAngle({0.0f, 1.0f});
  }

  // Zurücksetzen der Position
  m_spaceship_s->move(m_spaceMovement);
}