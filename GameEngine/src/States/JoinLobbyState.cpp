/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** JoinLobbyState
*/

#include "JoinLobbyState.hpp"

JoinLobbyState::JoinLobbyState(StateMachine &t_machine,
                               rtype::IRenderWindow *t_window,
                               MusicPlayer &t_music_player, std::size_t t_flag,
                               rtype::IGraphicLoader *t_graphic_loader,
                               int *t_level, const bool t_replace,
                               std::string t_ip, UdpClient *t_clientCom)
    : State(t_machine, t_window, t_music_player, t_graphic_loader, t_level,
            t_replace, t_ip, t_clientCom),
      m_home_btn(Button(
        "./assets/icons/white/home.png",
        rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 32),
                        static_cast<float>(m_window->getSize().y - 100)},
        rtype::Vector2f{64, 64}, t_graphic_loader)),
      m_start_btn(Button(
        "./assets/startBtn.png",
        rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 135),
                        static_cast<float>(m_window->getSize().y - 230)},
        rtype::Vector2f{270, 130}, t_graphic_loader)),
      m_textbox(Textbox(35, rtype::Black, true, t_graphic_loader)),
      m_join_btn(Button(
        "./assets/icons/white/buttonStart.png",
        rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 100),
                        static_cast<float>(m_window->getSize().y / 2 + 100)},
        rtype::Vector2f{200, 200}, t_graphic_loader)),
      m_flag(t_flag) {
  m_bg_t = m_graphic_loader->loadTexture();
  m_bg_s = m_graphic_loader->loadSprite();
  if (!m_bg_t->loadFromFile("./assets/menubg.jpg")) {
    throw std::runtime_error("Unable to load image.");
  }
  m_player_one_t = m_graphic_loader->loadTexture();
  m_player_one_s = m_graphic_loader->loadSprite();
  if (!m_player_one_t->loadFromFile("./assets/icons/white/gamepad1.png")) {
    throw std::runtime_error("Unable to load image.");
  }
  m_player_one_s->setTexture(m_player_one_t, true);
  m_player_one_s->setPosition(
    rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 150),
                    static_cast<float>(m_window->getSize().y / 2 - 150)});

  m_player_two_t = m_graphic_loader->loadTexture();
  m_player_two_s = m_graphic_loader->loadSprite();
  if (!m_player_two_t->loadFromFile("./assets/icons/white/gamepad2.png")) {
    throw std::runtime_error("Unable to load image.");
  }
  m_player_two_s->setTexture(m_player_two_t, true);
  m_player_two_s->setPosition(
    rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 + 50),
                    static_cast<float>(m_window->getSize().y / 2 - 150)});
  m_player_three_t = m_graphic_loader->loadTexture();
  m_player_three_s = m_graphic_loader->loadSprite();
  if (!m_player_three_t->loadFromFile("./assets/icons/white/gamepad3.png")) {
    throw std::runtime_error("Unable to load image.");
  }
  m_player_three_s->setTexture(m_player_three_t, true);
  m_player_three_s->setPosition(
    rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 150),
                    static_cast<float>(m_window->getSize().y / 2 + 50)});
  m_player_four_t = m_graphic_loader->loadTexture();
  m_player_four_s = m_graphic_loader->loadSprite();
  if (!m_player_four_t->loadFromFile("./assets/icons/white/gamepad4.png")) {
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
  m_title->setString("JOIN LOBBY");
  m_title->setCharacterSize(50);
  m_title->setPosition(
    {(size_x / 2) - (m_title->getLocalBounds().width / 2), 100});
  m_instructions = m_graphic_loader->loadText();
  m_instructions->setFont(m_font);
  m_instructions->setString("Please enter lobby code:");
  m_instructions->setCharacterSize(35);
  m_instructions->setPosition(
    {(size_x / 2) - (m_instructions->getLocalBounds().width / 2),
     static_cast<float>(m_window->getSize().y / 2 - 200)});
  m_music_player.play(MusicID::MENU_THEME);
  m_textbox.setLimit(true, 10);
  m_textbox.setPosition(rtype::Vector2f{
    static_cast<float>(m_window->getSize().x / 2 -
                       m_textbox.getText()->getLocalBounds().width / 2),
    static_cast<float>(m_window->getSize().y / 2 - 100)});
  m_is_pressed = false;
  // call protocol to join lobby
}

void JoinLobbyState::pause() { std::cout << "MenuState Pause\n"; }

void JoinLobbyState::resume() { std::cout << "MenuState resume\n"; }

void JoinLobbyState::update() {
  for (auto event = rtype::Event{}; m_window->pollEvent(event);) {
    rtype::Vector2i mouse_pos = m_mouse->getMousePosition(m_window);
    rtype::Vector2f mouse_pos_f{static_cast<float>(mouse_pos.x),
                                static_cast<float>(mouse_pos.y)};
    if (event.type == rtype::EventType::MouseMoved) {
      m_home_btn.is_hovered(mouse_pos_f);
      m_join_btn.is_hovered(mouse_pos_f);
      // m_start_btn.is_hovered(mouse_pos_f);
    }
    if (m_mouse->isLeftMouseButtonPressed()) {
      if (m_home_btn.is_pressed(mouse_pos_f)) {
        std::cout << "homebtn pressed" << std::endl;
        m_clientCom->m_lobby_code = "";
        m_next = StateMachine::build<MainState>(
          m_state_machine, m_window, m_music_player, m_flag, m_graphic_loader,
          m_level, true, m_ip, m_clientCom);
      }
      if (m_join_btn.is_pressed(mouse_pos_f) &&
          !m_is_pressed) {  // start game if pressed
        std::cout << "joinbtn pressed" << std::endl;
        m_clientCom->m_lobby_code = m_textbox.getTextString();
        std::cout << m_clientCom->m_lobby_code << std::endl;
        JoinLobbyAction join_lobby_action = JoinLobbyAction(
          Action::ActionType::JOINLOBBY, m_clientCom->m_lobby_code, "Nutzer");
        m_clientCom->sendMessage(join_lobby_action.getCommand());
        m_is_pressed = true;
      }

      if (m_clientCom->m_lobby_successfull_connected) {
        m_next = StateMachine::build<CreateLobbyState>(
          m_state_machine, m_window, m_music_player, m_flag, m_graphic_loader,
          m_level, true, m_ip, m_clientCom);
      }
    }
    switch (event.type) {
      case rtype::EventType::Closed:
        m_state_machine.quit();
        break;
      case rtype::EventType::KeyPressed:
        switch (event.key) {
          case rtype::EventKey::Enter:
            m_textbox.setSelected(true);
            break;
          case rtype::EventKey::Escape:
            m_textbox.setSelected(false);
            break;
          default:
            break;
        }
        break;
      case rtype::EventType::TextEntered:
        m_textbox.typedOn(event);
        m_textbox.setPosition(rtype::Vector2f{
          static_cast<float>(m_window->getSize().x / 2 -
                             m_textbox.getText()->getLocalBounds().width / 2),
          static_cast<float>(m_window->getSize().y / 2 - 100)});
        break;
      default:
        break;
    }
  }
}

void JoinLobbyState::draw() {
  m_window->clear();
  m_window->draw(m_bg_s);
  m_window->draw(m_title);
  m_window->draw(m_instructions);
  // m_window->draw(m_player_one_s); could add if statement to show icon depending on how many players are connected
  // m_window->draw(m_player_two_s);
  // m_window->draw(m_player_three_s);
  // m_window->draw(m_player_four_s);
  m_window->draw(m_home_btn.getSprite());
  m_window->draw(m_textbox.getText());
  if (m_textbox.getLength() == 10) { m_window->draw(m_join_btn.getSprite()); }
  // m_window->draw(m_start_btn.getSprite());
  m_window->display();
}
