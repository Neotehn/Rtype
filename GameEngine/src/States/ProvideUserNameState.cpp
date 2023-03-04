#include "ProvideUserNameState.hpp"

ProvideUserNameState::ProvideUserNameState(
  StateMachine &t_machine, rtype::IRenderWindow *t_window,
  MusicPlayer &t_music_player, std::size_t t_flag,
  rtype::IGraphicLoader *t_graphic_loader, int *t_level,
  const std::string &t_path_to_sprite, const bool t_replace, std::string t_ip,
  UdpClient *t_clientCom)
    : State(t_machine, t_window, t_music_player, t_graphic_loader, t_level,
            t_path_to_sprite, t_replace, t_ip, t_clientCom),
      m_home_btn(Button(
        "./assets/icons/white/home.png",
        rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 32),
                        static_cast<float>(m_window->getSize().y - 100)},
        rtype::Vector2f{64, 64}, t_graphic_loader, true)),
      m_textbox(Textbox(35, rtype::Black, true, t_graphic_loader)),
      m_flag(t_flag) {
  initSprites();
  initText();
  m_is_pressed = false;
}

void ProvideUserNameState::update() {
  bool pressed_enter = false;
  for (auto event = rtype::Event{}; m_window->pollEvent(event);) {
    rtype::Vector2i mouse_pos = m_mouse->getMousePosition(m_window);
    rtype::Vector2f mouse_pos_f{static_cast<float>(mouse_pos.x),
                                static_cast<float>(mouse_pos.y)};
    if (event.type == rtype::EventType::MouseMoved) {
      m_home_btn.is_hovered(mouse_pos_f);
      // m_start_btn.is_hovered(mouse_pos_f);
    }
    if (m_mouse->isLeftMouseButtonPressed()) {
      if (m_home_btn.is_pressed(mouse_pos_f)) {
        std::cout << "homebtn pressed" << std::endl;
        std::cout << m_clientCom->getPlayerName() << "  \n";
        m_clientCom->setPlayerName(m_textbox.getTextString());
        std::cout << m_clientCom->getPlayerName() << "  \n";
        m_next = StateMachine::build<MainState>(
          m_state_machine, m_window, m_music_player, m_flag, m_graphic_loader,
          m_level, m_path_to_sprite, true, m_ip, m_clientCom);
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
            if (m_textbox.getTextString().size() >= 3)
              pressed_enter = true;
            break;
          case rtype::EventKey::Escape:
            m_textbox.setSelected(false);
            break;
          default:
            break;
        }
        break;
      case rtype::EventType::TextEntered:
        if (pressed_enter) {
          m_clientCom->setPlayerName(m_textbox.getTextString());
          m_next = StateMachine::build<MainState>(
            m_state_machine, m_window, m_music_player, m_flag, m_graphic_loader,
            m_level, m_path_to_sprite, true, m_ip, m_clientCom);
          break;
        }
        if (event.key == rtype::EventKey::Enter ||
            event.key == 10 || m_textbox.getTextString().size() >= 7) {
          break;
        }
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

void ProvideUserNameState::draw() {
  m_window->clear();
  m_window->draw(m_bg_s);
  m_window->draw(m_title);
  m_window->draw(m_instructions);
  m_window->draw(m_home_btn.getSprite());
  m_window->draw(m_textbox.getText());
  m_window->display();
}

void ProvideUserNameState::initSprites() {
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
}

void ProvideUserNameState::initText() {
  float size_x = m_window->getSize().x;
  float size_y = m_window->getSize().y;

  m_font = m_graphic_loader->loadFont();
  if (!m_font->loadFromFile("./assets/font/nasalization-rg.ttf")) {
    throw std::runtime_error("Unable to load font.");
  }
  m_title = m_graphic_loader->loadText();
  m_title->setFont(m_font);
  m_title->setString("Welcome to RType");
  m_title->setCharacterSize(50);
  m_title->setPosition(
    {(size_x / 2) - (m_title->getLocalBounds().width / 2), 100});
  m_instructions = m_graphic_loader->loadText();
  m_instructions->setFont(m_font);
  m_instructions->setString("Please enter your username:");
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
}

void ProvideUserNameState::pause() { std::cout << "Pause" << std::endl; }

void ProvideUserNameState::resume() { std::cout << "Resume" << std::endl; }
