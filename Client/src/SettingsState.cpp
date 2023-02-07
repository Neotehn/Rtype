#include "../inc/SettingsState.hpp"
#include "../inc/MainState.hpp"
#include "../inc/PlayState.hpp"

SettingsState::SettingsState(StateMachine &t_machine,
                             sf::RenderWindow &t_window,
                             MusicPlayer &t_music_player, const bool t_replace)
    : State(t_machine, t_window, t_music_player, t_replace),
      m_start_btn(Button(
        "./assets/startBtn.png",
        sf::Vector2f(m_window.getSize().x - 320, m_window.getSize().y - 180),
        sf::Vector2f(270, 130))),
      m_vol_up(Button(
        "./assets/plus.png",
        sf::Vector2f(m_window.getSize().x / 2 - 100, m_window.getSize().y / 2),
        sf::Vector2f(64, 64))),
      m_vol_down(Button(
        "./assets/minus.png",
        sf::Vector2f(m_window.getSize().x / 2 + 50, m_window.getSize().y / 2),
        sf::Vector2f(64, 64))) {
  if (!m_bg_t.loadFromFile("./assets/menubg.jpg")) {
    throw std::runtime_error("Unable to load image.");
  }
  if (!m_font.loadFromFile("./assets/font/Sansation.ttf"))
    throw std::runtime_error("Unable to load font.");
  m_title.setString("SETTINGS");
  m_title.setFont(m_font);
  m_title.setCharacterSize(100);
  m_title.setPosition(
    m_window.getSize().x / 2 - m_title.getGlobalBounds().width / 2, 50);
  m_vol_txt.setString("VOLUME");
  m_vol_txt.setFont(m_font);
  m_vol_txt.setCharacterSize(50);
  m_vol_txt.setPosition(
    (m_window.getSize().x / 2) - m_vol_txt.getGlobalBounds().width / 2,
    m_window.getSize().y / 2 - (25 + m_vol_txt.getGlobalBounds().height));
  float size_x = m_window.getSize().x;
  float size_y = m_window.getSize().y;
  float scale_x = size_x / m_bg_t.getSize().x;
  float scale_y = size_y / m_bg_t.getSize().y;
  m_bg_s.setTexture(m_bg_t, true);
  m_bg_s.setScale(scale_x, scale_y);
  m_music_player.play(MusicID::MENUTHEME);
}

void SettingsState::pause() { std::cout << "MenuState Pause\n"; }

void SettingsState::resume() { std::cout << "MenuState resume\n"; }

void SettingsState::update() {
  for (auto event = sf::Event{}; m_window.pollEvent(event);) {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(m_window);
    sf::Vector2f mouse_pos_f(static_cast<float>(mouse_pos.x),
                             static_cast<float>(mouse_pos.y));
    if (event.type == sf::Event::MouseMoved) {
      m_start_btn.is_hovered(mouse_pos_f);
      m_vol_down.is_hovered(mouse_pos_f);
      m_vol_up.is_hovered(mouse_pos_f);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      if (m_start_btn.is_pressed(mouse_pos_f)) {
        std::cout << "startbtn pressed" << std::endl;
        m_next = StateMachine::build<MainState>(m_state_machine, m_window,
                                                m_music_player, true);
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
      case sf::Event::Closed:
        m_state_machine.quit();
        break;
      case sf::Event::KeyPressed:
        switch (event.key.code) {
          case sf::Keyboard::Space:
            m_next = StateMachine::build<MainState>(m_state_machine, m_window,
                                                    m_music_player, true);
            break;
          case sf::Keyboard::Escape:
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
  m_window.clear();
  m_window.draw(m_bg_s);
  m_window.draw(m_title);
  m_window.draw(m_vol_txt);
  m_window.draw(m_start_btn.getSprite());
  m_window.draw(m_vol_down.getSprite());
  m_window.draw(m_vol_up.getSprite());
  m_window.display();
}