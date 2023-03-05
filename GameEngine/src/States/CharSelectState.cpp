/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** CharSelectState
*/

#include "CharSelectState.hpp"

CharSelectState::CharSelectState(
  StateMachine &t_machine, rtype::IRenderWindow *t_window,
  MusicPlayer &t_music_player, std::size_t t_flag,
  rtype::IGraphicLoader *t_graphic_loader, int *t_level,
  const std::string &t_path_to_sprite, bool t_replace, std::string t_ip,
  UdpClient *t_clientCom)
    : State(t_machine, t_window, t_music_player, t_graphic_loader, t_level,
            t_path_to_sprite, t_replace, t_ip, t_clientCom),
      m_flag(t_flag),
      m_join_btn(Button(
        "./assets/startBtn.png",
        rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 65),
                        static_cast<float>(m_window->getSize().y / 2)},
        rtype::Vector2f{130, 50}, t_graphic_loader, false)),
      m_ship_blue(Button(
        "./assets/starship_blue.png",
        rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 250),
                        static_cast<float>(m_window->getSize().y / 2 - 200)},
        rtype::Vector2f{215.75, 215.75}, t_graphic_loader, false)),
      m_ship_green(Button(
        "./assets/starship_green.png",
        rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 + 35.25),
                        static_cast<float>(m_window->getSize().y / 2 - 200)},
        rtype::Vector2f{215.75, 215.75}, t_graphic_loader, false)),
      m_ship_pink(Button(
        "./assets/starship_pink.png",
        rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 250),
                        static_cast<float>(m_window->getSize().y / 2 + 115.75)},
        rtype::Vector2f{215.75, 215.75}, t_graphic_loader, false)),
      m_ship_yellow(Button(
        "./assets/starship_yellow.png",
        rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 + 35.25),
                        static_cast<float>(m_window->getSize().y / 2 + 115.75)},
        rtype::Vector2f{215.75, 215.75}, t_graphic_loader, false)) {
  initText();
  initSprites();
  m_is_pressed = false;
  m_selected_ship = "";
  m_music_player.play(MusicID::MENU_THEME);
}

CharSelectState::~CharSelectState() {}

void CharSelectState::initText() {
  m_font = m_graphic_loader->loadFont();
  if (!m_font->loadFromFile("./assets/font/nasalization-rg.ttf")) {
    throw std::runtime_error("Unable to load font.");
  }
  m_title = m_graphic_loader->loadText();
  m_title->setFont(m_font);
  m_title->setString("SELECT YOUR SHIP");
  m_title->setCharacterSize(50);
  m_title->setPosition(
    {(m_window->getSize().x / 2) - (m_title->getLocalBounds().width / 2), 100});
}

void CharSelectState::initSprites() {
  m_bg_t = m_graphic_loader->loadTexture();
  m_bg_s = m_graphic_loader->loadSprite();
  if (!m_bg_t->loadFromFile("./assets/menubg.jpg")) {
    throw std::runtime_error("Unable to load image.");
  }
  float scale_x =
    static_cast<float>(m_window->getSize().x) / m_bg_t->getSize().x;
  float scale_y =
    static_cast<float>(m_window->getSize().y) / m_bg_t->getSize().y;
  m_bg_s->setTexture(m_bg_t, true);
  m_bg_s->setScale({scale_x, scale_y});
}

void CharSelectState::update() {
  for (auto event = rtype::Event{}; m_window->pollEvent(event);) {
    rtype::Vector2i mouse_pos = m_mouse->getMousePosition(m_window);
    rtype::Vector2f mouse_pos_f{static_cast<float>(mouse_pos.x),
                                static_cast<float>(mouse_pos.y)};
    if (event.type == rtype::EventType::MouseMoved) {
      m_ship_blue.is_hovered(mouse_pos_f);
      m_ship_green.is_hovered(mouse_pos_f);
      m_ship_pink.is_hovered(mouse_pos_f);
      m_ship_yellow.is_hovered(mouse_pos_f);
      m_join_btn.is_hovered(mouse_pos_f);
    }
    if (m_mouse->isLeftMouseButtonPressed()) {
      if (m_join_btn.is_pressed(mouse_pos_f) && !m_is_pressed) {
        m_music_player.stop();
        m_next = StateMachine::build<GameState>(
          m_state_machine, m_window, m_music_player, m_flag, m_graphic_loader,
          m_level, m_selected_ship, true, "", m_clientCom);
        m_is_pressed = true;
      }
      if (m_ship_blue.is_pressed(mouse_pos_f)) {
        m_selected_ship = "../Client/assets/starship_blue.png";
      }
      if (m_ship_green.is_pressed(mouse_pos_f)) {
        m_selected_ship = "../Client/assets/starship_green.png";
      }
      if (m_ship_pink.is_pressed(mouse_pos_f)) {
        m_selected_ship = "../Client/assets/starship_pink.png";
      }
      if (m_ship_yellow.is_pressed(mouse_pos_f)) {
        m_selected_ship = "../Client/assets/starship_yellow.png";
      }
    }
    switch (event.type) {
      case rtype::EventType::Closed:
        m_state_machine.quit();
        break;
      default:
        break;
    }
  }
}

void CharSelectState::draw() {
  m_window->clear();
  m_window->draw(m_bg_s);
  m_window->draw(m_title);
  m_window->draw(m_join_btn.getSprite());
  m_window->draw(m_ship_blue.getSprite());
  m_window->draw(m_ship_green.getSprite());
  m_window->draw(m_ship_pink.getSprite());
  m_window->draw(m_ship_yellow.getSprite());
  m_window->display();
}