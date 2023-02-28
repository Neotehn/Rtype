#include "./SettingsState.hpp"

SettingsState::SettingsState(StateMachine &t_machine,
                             rtype::IRenderWindow *t_window,
                             MusicPlayer &t_music_player, std::size_t t_flag,
                             rtype::IGraphicLoader *t_graphic_loader,
                             int *t_level, const bool t_replace)
    : State(t_machine, t_window, t_music_player, t_graphic_loader, t_level,
            t_replace),
      m_start_btn(Button(
        "./assets/icons/home.png",
        rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 32),
                        static_cast<float>(m_window->getSize().y - 100)},
        rtype::Vector2f{64, 64}, t_graphic_loader)),
      m_vol_up(Button(
        "./assets/icons/plus.png",
        rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 - 81.5),
                        static_cast<float>(m_window->getSize().y / 2)},
        rtype::Vector2f{64, 64}, t_graphic_loader)),
      m_vol_down(Button(
        "./assets/icons/minus.png",
        rtype::Vector2f{static_cast<float>(m_window->getSize().x / 2 + 17.5),
                        static_cast<float>(m_window->getSize().y / 2)},
        rtype::Vector2f{64, 64}, t_graphic_loader)),
      m_flag(t_flag) {
  m_bg_t = m_graphic_loader->loadTexture();
  m_bg_s = m_graphic_loader->loadSprite();
  if (!m_bg_t->loadFromFile("./assets/menubg.jpg")) {
    throw std::runtime_error("Unable to load image.");
  }
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
  m_title->setString("SETTINGS");
  m_title->setCharacterSize(50);
  m_title->setPosition(
    {(size_x / 2) - (m_title->getLocalBounds().width / 2), 100});
  m_vol_txt = m_graphic_loader->loadText();
  m_vol_txt->setFont(m_font);
  m_vol_txt->setString("VOLUME");
  m_vol_txt->setCharacterSize(35);
  m_vol_txt->setPosition(
    {(size_x / 2) - (m_vol_txt->getLocalBounds().width / 2),
     (size_y / 2) - 50});
  m_music_player.play(MusicID::MENU_THEME);
}

SettingsState::~SettingsState() {
  delete m_bg_t;
  delete m_bg_s;
}

SettingsState::~SettingsState() {
  delete m_bg_t;
  delete m_bg_s;
}

void SettingsState::pause() { std::cout << "MenuState Pause\n"; }

void SettingsState::resume() { std::cout << "MenuState resume\n"; }

void SettingsState::update() {
  for (auto event = rtype::Event{}; m_window->pollEvent(event);) {
    rtype::Vector2i mouse_pos = m_mouse->getMousePosition(m_window);
    rtype::Vector2f mouse_pos_f{static_cast<float>(mouse_pos.x),
                                static_cast<float>(mouse_pos.y)};
    if (event.type == rtype::EventType::MouseMoved) {
      m_start_btn.is_hovered(mouse_pos_f);
      m_vol_down.is_hovered(mouse_pos_f);
      m_vol_up.is_hovered(mouse_pos_f);
    }
    if (m_mouse->isLeftMouseButtonPressed()) {
      if (m_start_btn.is_pressed(mouse_pos_f)) {
        std::cout << "startbtn pressed" << std::endl;
        m_next = StateMachine::build<MainState>(
          m_state_machine, m_window, m_music_player, m_flag, m_graphic_loader,
          m_level, true);
      }
      if (m_vol_down.is_pressed(mouse_pos_f)) {
        if (m_music_player.getVolume() > 0) {
          float tmp_vol = m_music_player.getVolume();
          m_music_player.setVolume(tmp_vol - 5);
        }
      }
      if (m_vol_up.is_pressed(mouse_pos_f)) {
        if (m_music_player.getVolume() < 100) {
          float tmp_vol = m_music_player.getVolume();
          m_music_player.setVolume(tmp_vol + 5);
        }
      }
      if (m_vol_down.is_pressed(mouse_pos_f)) {
        if (m_music_player.getVolume() > 0) {
          float tmp_vol = m_music_player.getVolume();
          m_music_player.setVolume(tmp_vol - 5);
        }
      }
      if (m_vol_up.is_pressed(mouse_pos_f)) {
        if (m_music_player.getVolume() < 100) {
          float tmp_vol = m_music_player.getVolume();
          m_music_player.setVolume(tmp_vol + 5);
        }
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

void SettingsState::draw() {
  m_window->clear();
  m_window->draw(m_bg_s);
  m_window->draw(m_title);
  m_window->draw(m_vol_txt);
  m_window->draw(m_start_btn.getSprite());
  m_window->draw(m_vol_down.getSprite());
  m_window->draw(m_vol_up.getSprite());
  m_window->display();
}
