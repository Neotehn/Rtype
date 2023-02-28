/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** LobbyState
*/

#include "CreateLobbyState.hpp"

CreateLobbyState::CreateLobbyState(StateMachine &t_machine,
                                   rtype::IRenderWindow *t_window,
                                   MusicPlayer &t_music_player,
                                   std::size_t t_flag,
                                   rtype::IGraphicLoader *t_graphic_loader,
                                   const bool t_replace)
    : State(t_machine, t_window, t_music_player, t_graphic_loader, t_replace),
      m_home_btn(Button(
        "./assets/icons/home.png",
        rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 32),
                        static_cast<float>(m_window->getSize().y - 100)},
        rtype::Vector2f{64, 64}, t_graphic_loader)),
      m_start_btn(Button(
        "./assets/startBtn.png",
        rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 135),
                        static_cast<float>(m_window->getSize().y - 230)},
        rtype::Vector2f{270, 130}, t_graphic_loader)),
      m_flag(t_flag) {
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
  m_player_three_t = m_graphic_loader->loadTexture();
  m_player_three_s = m_graphic_loader->loadSprite();
  if (!m_player_three_t->loadFromFile("./assets/icons/gamepad3.png")) {
    throw std::runtime_error("Unable to load image.");
  }
  m_player_three_s->setTexture(m_player_three_t, true);
  m_player_three_s->setPosition(
    rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 150),
                    static_cast<float>(m_window->getSize().y / 2 + 50)});
  m_player_four_t = m_graphic_loader->loadTexture();
  m_player_four_s = m_graphic_loader->loadSprite();
  if (!m_player_four_t->loadFromFile("./assets/icons/gamepad4.png")) {
    throw std::runtime_error("Unable to load image.");
  }
  m_player_four_s->setTexture(m_player_four_t, true);
  m_player_four_s->setPosition(
    rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 + 50),
                    static_cast<float>(m_window->getSize().y / 2 + 50)});
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
  m_title->setString("CREATE LOBBY");
  m_title->setCharacterSize(50);
  m_title->setPosition(
    {(size_x / 2) - (m_title->getLocalBounds().width / 2), 100});
  m_music_player.play(MusicID::MENU_THEME);
  // call protocol for creating lobby
}

void CreateLobbyState::pause() { std::cout << "MenuState Pause\n"; }

void CreateLobbyState::resume() { std::cout << "MenuState resume\n"; }

void CreateLobbyState::update() {
  for (auto event = rtype::Event{}; m_window->pollEvent(event);) {
    rtype::Vector2i mouse_pos = m_mouse->getMousePosition(m_window);
    rtype::Vector2f mouse_pos_f{static_cast<float>(mouse_pos.x),
                                static_cast<float>(mouse_pos.y)};
    if (event.type == rtype::EventType::MouseMoved) {
      m_home_btn.is_hovered(mouse_pos_f);
      m_start_btn.is_hovered(mouse_pos_f);
    }
    if (m_mouse->isLeftMouseButtonPressed()) {
      if (m_home_btn.is_pressed(mouse_pos_f)) {
        std::cout << "homebtn pressed" << std::endl;
        m_next = StateMachine::build<MainState>(m_state_machine, m_window,
                                                m_music_player, m_flag,
                                                m_graphic_loader, true);
      }
      if (m_start_btn.is_pressed(mouse_pos_f)) {  // start game if pressed
        std::cout << "startbtn pressed" << std::endl;
        m_next = StateMachine::build<GameState>(m_state_machine, m_window,
                                                m_music_player, m_flag,
                                                m_graphic_loader, true);
      }
    }
    switch (event.type) {
      case rtype::EventType::Closed:
        m_state_machine.quit();
        break;
      case rtype::EventType::KeyPressed:
        switch (event.key) {
          case rtype::EventKey::Escape:
            m_next = StateMachine::build<MainState>(m_state_machine, m_window,
                                                    m_music_player, m_flag,
                                                    m_graphic_loader, true);
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

void CreateLobbyState::draw() {
  m_window->clear();
  m_window->draw(m_bg_s);
  m_window->draw(m_title);
  // m_window->draw(m_player_one_s); could add if statement to show icon depending on how many players are connected
  // m_window->draw(m_player_two_s);
  // m_window->draw(m_player_three_s);
  // m_window->draw(m_player_four_s);
  m_window->draw(m_home_btn.getSprite());
  m_window->draw(m_start_btn.getSprite());
  m_window->display();
}
