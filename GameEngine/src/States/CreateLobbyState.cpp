/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** LobbyState
*/

#include "CreateLobbyState.hpp"

void CreateLobbyState::initSprites() {
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
  m_player_one_t = m_graphic_loader->loadTexture();
  m_player_one_s = m_graphic_loader->loadSprite();
  if (!m_player_one_t->loadFromFile("./assets/icons/white/gamepad1.png")) {
    throw std::runtime_error("Unable to load image.");
  }
  m_player_one_s->setTexture(m_player_one_t, true);
  m_player_one_s->setPosition(
    rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 150 - 50),
                    static_cast<float>(m_window->getSize().y / 2 - 150)});

  m_player_two_t = m_graphic_loader->loadTexture();
  m_player_two_s = m_graphic_loader->loadSprite();
  if (!m_player_two_t->loadFromFile("./assets/icons/white/gamepad2.png")) {
    throw std::runtime_error("Unable to load image.");
  }
  m_player_two_s->setTexture(m_player_two_t, true);
  m_player_two_s->setPosition(
    rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 + 50 + 50),
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
  m_bg_text = m_graphic_loader->loadRectangleShape();
  SpriteECS sprite_bg_text =
    SpriteECS("./../Client/assets/bg_textbox.png", m_graphic_loader);
  m_bg_text->setTexture(sprite_bg_text.getTexture());
  m_bg_text->setTextureRect({0, 0, 1018, 1938});
  m_bg_text->setRotation(180);
  m_bg_text->setSize({size_x / 2 + 100, 80});
  m_bg_text->setPosition({size_x / 2 + 105, size_y - 5});
}

void CreateLobbyState::initText() {
  float size_x = m_window->getSize().x;
  float size_y = m_window->getSize().y;
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

  m_player_one_text = m_graphic_loader->loadText();
  m_player_one_text->setFont(m_font);
  m_player_one_text->setString("CREATE LOBBY");
  m_player_one_text->setCharacterSize(50);
  m_player_one_text->setPosition(
    {(size_x / 2) - 50 - (m_player_one_text->getLocalBounds().width / 2), 350});

  m_player_two_text = m_graphic_loader->loadText();
  m_player_two_text->setFont(m_font);
  m_player_two_text->setString("CREATE LOBBY");
  m_player_two_text->setCharacterSize(50);
  m_player_two_text->setPosition(
    {(size_x / 2) + 50 + (m_player_one_text->getLocalBounds().width / 2) -
       (m_player_two_text->getLocalBounds().width / 2),
     350});

  m_lobby_code_text = m_graphic_loader->loadText();
  m_lobby_code_text->setFont(m_font);
  m_lobby_code_text->setString(m_clientCom->m_lobby_code);
  m_lobby_code_text->setCharacterSize(50);
  m_lobby_code_text->setColor(rtype::Black);
  m_lobby_code_text->setPosition(
    {(size_x / 2) - (m_lobby_code_text->getLocalBounds().width / 2), 500});
  m_chat_title = m_graphic_loader->loadText();
  m_chat_title->setFont(m_font);
  m_chat_title->setString("CHAT:");
  m_chat_title->setCharacterSize(20);
  // m_chat_title->setColor({18, 107, 165, 255});
  m_chat_title->setPosition(
    {20, static_cast<float>(m_window->getSize().y - 70)});
  m_placeholder = m_graphic_loader->loadText();
  m_placeholder->setFont(m_font);
  m_placeholder->setString("PRESS ENTER FOR CHAT");
  m_placeholder->setCharacterSize(20);
  // m_placeholder->setColor({18, 107, 165, 255});
  m_placeholder->setPosition(
    {20, static_cast<float>(m_window->getSize().y - 40)});
  m_chat.setLimit(true, 20);
  m_chat.setPosition(
    rtype::Vector2f{20, static_cast<float>(m_window->getSize().y - 40)});
}

void CreateLobbyState::initChad() {
  for (int i = 0; i < 10; i++) {
    rtype::IText *tmp = m_graphic_loader->loadText();
    tmp->setFont(m_font);
    tmp->setString("");
    tmp->setCharacterSize(20);
    m_chad_messages.push_back(tmp);
  }
}

CreateLobbyState::CreateLobbyState(
  StateMachine &t_machine, rtype::IRenderWindow *t_window,
  MusicPlayer &t_music_player, std::size_t t_flag,
  rtype::IGraphicLoader *t_graphic_loader, int *t_level,
  const std::string &t_path_to_sprite, const bool t_replace, std::string t_ip,
  UdpClient *t_clientCom)
    : State(t_machine, t_window, t_music_player, t_graphic_loader, t_level,
            t_replace, t_ip, t_clientCom),
      m_home_btn(
        Button("./assets/icons/white/home.png",
               rtype::Vector2f{static_cast<float>(m_window->getSize().x - 100),
                               static_cast<float>(m_window->getSize().y - 100)},
               rtype::Vector2f{64, 64}, t_graphic_loader, true)),
      m_start_btn(Button(
        "./assets/startBtn.png",
        rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 65),
                        static_cast<float>(m_window->getSize().y - 230)},
        rtype::Vector2f{130, 50}, t_graphic_loader, false)),
      m_chat(Textbox(20, rtype::White, false, t_graphic_loader)),
      m_flag(t_flag) {
  initSprites();
  initText();
  initChad();
  m_music_player.play(MusicID::MENU_THEME);
  // call protocol for creating lobby
}

void CreateLobbyState::pause() { std::cout << "MenuState Pause\n"; }

void CreateLobbyState::resume() { std::cout << "MenuState resume\n"; }

void CreateLobbyState::update() {
  for (int i = 0; i < m_clientCom->m_chad_msgs.size(); i++) {
    m_chad_messages[i]->setString(m_clientCom->m_chad_msgs[i]);
    m_chad_messages[i]->setPosition({20, static_cast<float>(100 + (i * 50))});
  }
  for (int i = 9; i > m_clientCom->m_chad_msgs.size(); i--) {
    m_chad_messages[i]->setString("");
  }
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
        LeaveLobbyAction create_lobby_action = LeaveLobbyAction(
          Action::ActionType::LEAVELOBBY, m_clientCom->m_lobby_code,
          m_clientCom->getPlayerName());
        m_clientCom->sendMessage(create_lobby_action.getCommand());
        m_clientCom->m_lobby_code = "";
        m_clientCom->m_lobby_successfull_connected = false;
        m_next = StateMachine::build<MainState>(
          m_state_machine, m_window, m_music_player, m_flag, m_graphic_loader,
          m_level, m_path_to_sprite, true, "", m_clientCom);
      }
      if (m_start_btn.is_pressed(mouse_pos_f) &&
          m_clientCom->m_lobby_names.size() == 2) {  // start game if pressed
        std::cout << "startbtn pressed" << std::endl;
        m_next = StateMachine::build<GameState>(
          m_state_machine, m_window, m_music_player, m_flag, m_graphic_loader,
          m_level, m_path_to_sprite, true, "", m_clientCom);
      }  // currently lobby is just set between main and game
    }
    switch (event.type) {
      case rtype::EventType::Closed:
        m_state_machine.quit();
        break;
      case rtype::EventType::KeyPressed:
        switch (event.key) {
          case rtype::EventKey::Enter:
            if (m_chat.getSelected() && m_chat.getTextString() != "_") {
              std::cout << "prep push\n";
              ChadAction chad_action =
                ChadAction(Action::ActionType::CHAD, m_chat.getTextString(),
                           m_clientCom->m_lobby_code);
              m_clientCom->sendMessage(chad_action.getCommand());
              m_chat.resetString();

              std::cout << "reset string textbox\n";
            } else {
              m_chat.setSelected(true);
            }
            break;
          case rtype::EventKey::Escape:
            m_chat.setSelected(false);
          default:
            break;
        }
        break;
      case rtype::EventType::TextEntered:
        m_chat.typedOn(event);
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
  m_window->draw(m_lobby_code_text);
  for (int i = 0; i < m_clientCom->m_lobby_names.size(); i++) {
    if (i == 0) {
      m_player_one_text->setString(m_clientCom->m_lobby_names[i]);
      m_window->draw(m_player_one_text);
      m_window->draw(m_player_one_s);
    } else {
      m_player_two_text->setString(m_clientCom->m_lobby_names[i]);
      m_window->draw(m_player_two_text);
      m_window->draw(m_player_two_s);
    }
  }
  // m_window->draw(m_player_three_s);
  // m_window->draw(m_player_four_s);
  m_window->draw(m_bg_text);
  m_window->draw(m_chat_title);
  if (!m_chad_messages.empty()) {
    for (int i = 0; i < m_clientCom->m_chad_msgs.size(); i++) {
      m_window->draw(m_chad_messages[i]);
    }
  }
  if (m_chat.getSelected()) {
    m_window->draw(m_chat.getText());
  } else {
    m_window->draw(m_placeholder);
  }
  m_window->draw(m_home_btn.getSprite());
  if (m_clientCom->m_lobby_names.size() == 2)
    m_window->draw(m_start_btn.getSprite());
  m_window->display();
}
