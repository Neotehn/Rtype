#include "../inc/MainState.hpp"
#include "../inc/PlayState.hpp"
#include "../inc/SettingsState.hpp"

MainState::MainState(StateMachine &t_machine, sf::RenderWindow &t_window,
                     MusicPlayer &t_music_player, const bool t_replace)
    : State(t_machine, t_window, t_music_player, t_replace),
      m_start_btn(Button("./assets/startBtn.png",
                         sf::Vector2f(m_window.getSize().x / 2 - 135,
                                      m_window.getSize().y / 2 - 65),
                         sf::Vector2f(270, 130))),
      m_settings_btn(Button(
        "./assets/gear.png",
        sf::Vector2f(m_window.getSize().x - 100, m_window.getSize().y - 100),
        sf::Vector2f(64, 64))) {
  if (!m_bg_t.loadFromFile("./assets/menubg.jpg")) {
    throw std::runtime_error("Unable to load image.");
  }
  float size_x = m_window.getSize().x;
  float size_y = m_window.getSize().y;
  float scale_x = size_x / m_bg_t.getSize().x;
  float scale_y = size_y / m_bg_t.getSize().y;
  m_bg_s.setTexture(m_bg_t, true);
  m_bg_s.setScale(scale_x, scale_y);
  m_music_player.play(MusicID::MENUTHEME);
}

void MainState::pause() { std::cout << "MenuState Pause\n"; }

void MainState::resume() { std::cout << "MenuState resume\n"; }

void MainState::update() {
  for (auto event = sf::Event{}; m_window.pollEvent(event);) {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(m_window);
    sf::Vector2f mouse_pos_f(static_cast<float>(mouse_pos.x),
                             static_cast<float>(mouse_pos.y));
    if (event.type == sf::Event::MouseMoved) {
      m_start_btn.is_hovered(mouse_pos_f);
      m_settings_btn.is_hovered(mouse_pos_f);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      if (m_start_btn.is_pressed(mouse_pos_f)) {
        std::cout << "startbtn pressed" << std::endl;
        m_next = StateMachine::build<PlayState>(m_state_machine, m_window,
                                                m_music_player, true);
      }
      if (m_settings_btn.is_pressed(mouse_pos_f)) {
        std::cout << "settingsbtn pressed" << std::endl;
        m_next = StateMachine::build<SettingsState>(m_state_machine, m_window,
                                                    m_music_player, true);
      }
    }
    switch (event.type) {
      case sf::Event::Closed:
        m_state_machine.quit();
        break;
      case sf::Event::KeyPressed:
        switch (event.key.code) {
          case sf::Keyboard::Space:
            m_next = StateMachine::build<PlayState>(m_state_machine, m_window,
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

void MainState::draw() {
  m_window.clear();
  m_window.draw(m_bg_s);
  m_window.draw(m_start_btn.getSprite());
  m_window.draw(m_settings_btn.getSprite());
  m_window.display();
}