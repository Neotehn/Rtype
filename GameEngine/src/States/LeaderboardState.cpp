#include "LeaderboardState.hpp"

LeaderboardState::LeaderboardState(StateMachine &t_machine,
                                   rtype::IRenderWindow *t_window,
                                   MusicPlayer &t_music_player,
                                   std::size_t t_flag,
                                   rtype::IGraphicLoader *t_graphic_loader,
                                   int *t_level,
                                   const std::string &t_path_to_sprite,
                                   bool t_replace, std::string t_ip,
                                   UdpClient *t_clientCom)
    : State(t_machine, t_window, t_music_player, t_graphic_loader, t_level,
            t_path_to_sprite, t_replace, t_ip, t_clientCom),
      m_next_btn(Button(
        "./assets/homeBtn.png",
        rtype::Vector2f{static_cast<float>(m_window->getSize().x - 150),
                        static_cast<float>(m_window->getSize().y - 50)},
        rtype::Vector2f{150, 50}, t_graphic_loader, false)),
      m_flag(t_flag) {
  std::cout << "init leaderboard" << std::endl;
  m_path_to_sprite = t_path_to_sprite;

  initSprites();
  initText();
  m_sound_manager.init(m_graphic_loader, false);
}



LeaderboardState::LeaderboardState(StateMachine &t_machine,
                                   rtype::IRenderWindow *t_window,
                                   MusicPlayer &t_music_player,
                                   std::size_t t_flag,
                                   rtype::IGraphicLoader *t_graphic_loader,
                                   int *t_level,
                                   const std::string &t_path_to_sprite, bool t_music,
                                   bool t_replace, std::string t_ip,
                                   UdpClient *t_clientCom)
    : State(t_machine, t_window, t_music_player, t_graphic_loader, t_level,
            t_path_to_sprite, t_replace, t_ip, t_clientCom),
      m_next_btn(Button(
        "./assets/homeBtn.png",
        rtype::Vector2f{static_cast<float>(m_window->getSize().x - 150),
                        static_cast<float>(m_window->getSize().y - 50)},
        rtype::Vector2f{150, 50}, t_graphic_loader, false)),
      m_flag(t_flag) {
  std::cout << "init leaderboard" << std::endl;
  m_path_to_sprite = t_path_to_sprite;
  if (t_music)
    m_music_player.play(MusicID::MENU_THEME);
  initSprites();
  initText();
  m_sound_manager.init(m_graphic_loader, false);
}

LeaderboardState::~LeaderboardState() {
  delete m_bg_t;
  delete m_bg_s;
  delete m_font;
  delete m_title;
  for (auto &it : m_leaderboard_list) {
    delete it;
  }
}

void LeaderboardState::update() {
  for (auto event = rtype::Event{}; m_window->pollEvent(event);) {
    rtype::Vector2i mouse_pos = m_mouse->getMousePosition(m_window);
    rtype::Vector2f mouse_pos_f{static_cast<float>(mouse_pos.x),
                                static_cast<float>(mouse_pos.y)};
    if (event.type == rtype::EventType::MouseMoved) {
      m_next_btn.is_hovered(mouse_pos_f);
    }
    if (m_mouse->isLeftMouseButtonPressed()) {
      if (m_next_btn.is_pressed(mouse_pos_f)) {
        std::cout << "Mainmenubtn pressed" << std::endl;
        m_next = StateMachine::build<MainState>(
          m_state_machine, m_window, m_music_player, m_flag, m_graphic_loader,
          m_level, m_path_to_sprite, true, m_ip, m_clientCom);
        return ;
      }
    }
    switch (event.type) {
      case rtype::EventType::Closed:
        m_state_machine.quit();
        break;
      case rtype::EventType::KeyPressed:
        switch (event.key) {
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

void LeaderboardState::initSprites() {
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
}

void LeaderboardState::initText() {
  float size_x = m_window->getSize().x;
  float size_y = m_window->getSize().y;

  m_font = m_graphic_loader->loadFont();
  if (!m_font->loadFromFile("./assets/font/nasalization-rg.ttf")) {
    throw std::runtime_error("Unable to load font.");
  }
  m_title = m_graphic_loader->loadText();
  m_title->setFont(m_font);
  m_title->setString("HIGHSCORES");
  m_title->setCharacterSize(50);
  m_title->setPosition(
    {(size_x / 2) - (m_title->getLocalBounds().width / 2), 100});

  for (int i = 0; i < 10; i++) {
    rtype::IText *text = m_graphic_loader->loadText();
    text->setFont(m_font);
    text->setString( std::to_string(i+1) + ": ");
    text->setCharacterSize(30);
    text->setPosition(
      {(size_x / 2) - 100, static_cast<float>(200 + (i * 50))});
    m_leaderboard_list.push_back(text);
  }
  setLeaderboard(m_clientCom->getLeaderboard());
}

void LeaderboardState::draw() {
  m_window->clear();
  m_window->draw(m_bg_s);
  m_window->draw(m_next_btn.getSprite());
  m_window->draw(m_title);
  for (auto &text : m_leaderboard_list) {
    m_window->draw(text);
  }
  m_window->display();
}

void LeaderboardState::setLeaderboard(std::vector<std::string> t_leaderboard) {
  std::cout << "Leaderboard size: " << t_leaderboard.size() << std::endl;
  for (int i = 0; i < t_leaderboard.size(); i++) {
    m_leaderboard_list[i]->setString(t_leaderboard[i]);
  }
}