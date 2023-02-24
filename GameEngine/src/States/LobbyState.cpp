/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** LobbyState
*/

#include "LobbyState.hpp"

LobbyState::LobbyState(StateMachine &t_machine, rtype::IRenderWindow *t_window,
                       MusicPlayer &t_music_player, std::size_t t_flag,
                       const bool t_replace)
    : State(t_machine, t_window, t_music_player, t_replace),
      m_start_btn(Button(
        "./assets/startBtn.png",
        rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 135),
                        static_cast<float>(m_window->getSize().y / 2 - 65)},
        rtype::Vector2f{270, 130})),
      m_settings_btn(
        Button("./assets/icons/gear.png",
               rtype::Vector2f{static_cast<float>(m_window->getSize().x - 100),
                               static_cast<float>(m_window->getSize().y - 100)},
               rtype::Vector2f{64, 64})),
      m_flag(t_flag) {
  m_bg_t = new rtype::Texture();
  m_bg_s = new rtype::Sprite();
  if (!m_bg_t->loadFromFile("./assets/menubg.jpg")) {
    throw std::runtime_error("Unable to load image.");
  }
  float size_x = m_window->getSize().x;
  float size_y = m_window->getSize().y;
  float scale_x = size_x / m_bg_t->getSize().x;
  float scale_y = size_y / m_bg_t->getSize().y;
  m_bg_s->setTexture(m_bg_t, true);
  m_bg_s->setScale({scale_x, scale_y});
  m_font = new rtype::Font();
  if (!m_font->loadFromFile("./assets/font/nasalization-rg.ttf")) {
    throw std::runtime_error("Unable to load font.");
  }
  m_title = new rtype::Text();
  m_title->setFont(m_font);
  m_title->setString("LOBBY");
  m_title->setCharacterSize(50);
  m_title->setPosition(
    {(size_x / 2) - (m_title->getLocalBounds().width / 2), 100});
  m_music_player.play(MusicID::MENU_THEME);
}

void LobbyState::pause() { std::cout << "MenuState Pause\n"; }

void LobbyState::resume() { std::cout << "MenuState resume\n"; }

void LobbyState::update() {
  for (auto event = rtype::Event{}; m_window->pollEvent(event);) {
    rtype::Vector2i mouse_pos = m_mouse->getMousePosition(m_window);
    rtype::Vector2f mouse_pos_f{static_cast<float>(mouse_pos.x),
                                static_cast<float>(mouse_pos.y)};
    if (event.type == rtype::EventType::MouseMoved) {
      m_start_btn.is_hovered(mouse_pos_f);
      m_settings_btn.is_hovered(mouse_pos_f);
    }
    if (m_mouse->isLeftMouseButtonPressed()) {
      if (m_start_btn.is_pressed(mouse_pos_f)) {
        std::cout << "startbtn pressed" << std::endl;
        m_next = StateMachine::build<GameState>(m_state_machine, m_window,
                                                m_music_player, m_flag, true);
      }
      if (m_settings_btn.is_pressed(mouse_pos_f)) {
        std::cout << "settingsbtn pressed" << std::endl;
        m_next = StateMachine::build<SettingsState>(
          m_state_machine, m_window, m_music_player, m_flag, true);
      }
    }
    switch (event.type) {
      case rtype::EventType::Closed:
        m_state_machine.quit();
        break;
      case rtype::EventType::KeyPressed:
        switch (event.key) {
          case rtype::EventKey::Escape:
            m_next = StateMachine::build<MainState>(
              m_state_machine, m_window, m_music_player, m_flag, true);
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

void LobbyState::draw() {
  m_window->clear();
  m_window->draw(m_bg_s);
  m_window->draw(m_title);
  m_window->draw(m_start_btn.getSprite());
  m_window->draw(m_settings_btn.getSprite());
  m_window->display();
}
