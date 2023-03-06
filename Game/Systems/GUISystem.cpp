/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** GUISystem
*/

#include "GUISystem.hpp"

void GUISystem::initText() {
  m_font = m_graphic_loader->loadFont();
  if (!m_font->loadFromFile("./assets/font/nasalization-rg.ttf")) {
    throw std::runtime_error("Unable to load font.");
  }
  m_nb_total_coins = m_graphic_loader->loadText();
  m_nb_total_coins->setFont(m_font);
  m_nb_total_coins->setString("0 (TOTAL)");
  m_nb_total_coins->setCharacterSize(30);
  m_nb_total_coins->setPosition({50, static_cast<float>(10)});

  m_nb_money_shots = m_graphic_loader->loadText();
  m_nb_money_shots->setFont(m_font);
  m_nb_money_shots->setString("0x");
  m_nb_money_shots->setCharacterSize(30);
  m_nb_money_shots->setPosition(
    {static_cast<float>(m_window->getSize().x - 90), static_cast<float>(10)});

  m_nb_bomb_shots = m_graphic_loader->loadText();
  m_nb_bomb_shots->setFont(m_font);
  m_nb_bomb_shots->setString("0x");
  m_nb_bomb_shots->setCharacterSize(30);
  m_nb_bomb_shots->setPosition(
    {static_cast<float>(m_window->getSize().x - 280), static_cast<float>(10)});

  m_nb_fire_shots = m_graphic_loader->loadText();
  m_nb_fire_shots->setFont(m_font);
  m_nb_fire_shots->setString("0x");
  m_nb_fire_shots->setCharacterSize(30);
  m_nb_fire_shots->setPosition(
    {static_cast<float>(m_window->getSize().x - 430), static_cast<float>(10)});

  m_nb_coins = m_graphic_loader->loadText();
  m_nb_coins->setFont(m_font);
  m_nb_coins->setString("0");
  m_nb_coins->setCharacterSize(30);
  m_nb_coins->setPosition({50, static_cast<float>(m_window->getSize().y - 40)});
  m_nb_kills = m_graphic_loader->loadText();
  m_nb_kills->setFont(m_font);
  m_nb_kills->setString("0");
  m_nb_kills->setCharacterSize(30);
  m_nb_kills->setPosition({static_cast<float>(m_window->getSize().x / 2 + 5),
                           static_cast<float>(m_window->getSize().y - 40)});
  m_nb_exp = m_graphic_loader->loadText();
  m_nb_exp->setFont(m_font);
  m_nb_exp->setString("0");
  m_nb_exp->setCharacterSize(30);
  m_nb_exp->setPosition(
    {static_cast<float>(m_window->getSize().x -
                        (m_nb_exp->getLocalBounds().width + 10)),
     static_cast<float>(m_window->getSize().y - 40)});
  m_kills = m_graphic_loader->loadText();
  m_kills->setFont(m_font);
  m_kills->setString("KILLS:");
  m_kills->setCharacterSize(30);
  m_kills->setPosition(
    {static_cast<float>(m_window->getSize().x / 2 -
                        (m_kills->getLocalBounds().width + 5)),
     static_cast<float>(m_window->getSize().y - 40)});
  m_exp = m_graphic_loader->loadText();
  m_exp->setFont(m_font);
  m_exp->setString("EXP:");
  m_exp->setCharacterSize(30);
  m_exp->setPosition({static_cast<float>(m_window->getSize().x -
                                         (m_nb_exp->getLocalBounds().width +
                                          20 + m_exp->getLocalBounds().width)),
                      static_cast<float>(m_window->getSize().y - 40)});
}

GUISystem::GUISystem(std::shared_ptr<EntityManager> t_em,
                     rtype::IGraphicLoader *t_graphic_loader,
                     rtype::IRenderWindow *t_window, UdpClient *t_clientCom) {
  m_em = t_em;
  m_graphic_loader = t_graphic_loader;
  m_window = t_window;
  m_clientCom = t_clientCom;
  initText();
  SpriteECS sprite =
    SpriteECS("./../Client/sprites/powerup/coin.png", t_graphic_loader);
  m_coin = m_graphic_loader->loadRectangleShape();
  m_coin->setTexture(sprite.getTexture());
  m_coin->setSize({30, 30});
  m_coin->setPosition({10, static_cast<float>(m_window->getSize().y - 40)});
  m_coin->setTextureRect(rtype::IntRect{0, 0, 84, 84});

  SpriteECS sprite_coin =
    SpriteECS("./../Client/sprites/powerup/coin.png", t_graphic_loader);
  m_second_coin = m_graphic_loader->loadRectangleShape();
  m_second_coin->setTexture(sprite_coin.getTexture());
  m_second_coin->setSize({30, 30});
  m_second_coin->setPosition({10, static_cast<float>(10)});
  m_second_coin->setTextureRect(rtype::IntRect{0, 0, 84, 84});

  SpriteECS sprite_bomb =
    SpriteECS("./../Client/sprites/powerup/bomb_item.png", t_graphic_loader);
  m_bomb = m_graphic_loader->loadRectangleShape();
  m_bomb->setTexture(sprite_bomb.getTexture());
  m_bomb->setSize({30, 30});
  m_bomb->setPosition(
    {static_cast<float>(m_window->getSize().x - 330), static_cast<float>(10)});
  m_bomb->setTextureRect(rtype::IntRect{0, 0, 361, 361});

  SpriteECS sprite_fire =
    SpriteECS("./../Client/sprites/powerup/fire_item.png", t_graphic_loader);
  m_fire = m_graphic_loader->loadRectangleShape();
  m_fire->setTexture(sprite_fire.getTexture());
  m_fire->setSize({30, 30});
  m_fire->setPosition(
    {static_cast<float>(m_window->getSize().x - 480), static_cast<float>(10)});
  m_fire->setTextureRect(rtype::IntRect{0, 0, 361, 361});

  SpriteECS sprite_money =
    SpriteECS("./../Client/sprites/dollarPaul.png", t_graphic_loader);
  m_money = m_graphic_loader->loadRectangleShape();
  m_money->setTexture(sprite_money.getTexture());
  m_money->setSize({70, 30});
  m_money->setPosition(
    {static_cast<float>(m_window->getSize().x - 180), static_cast<float>(10)});
  m_money->setTextureRect(rtype::IntRect{0, 0, 800, 340});

  m_bg = m_graphic_loader->loadRectangleShape();
  SpriteECS spritebg =
    SpriteECS("./../Client/assets/bg_stats.png", t_graphic_loader);
  m_bg->setTexture(spritebg.getTexture());
  m_bg->setSize({static_cast<float>(m_window->getSize().x), 50});
  m_bg->setPosition({0, static_cast<float>(m_window->getSize().y - 50)});
  m_bg->setTextureRect(
    rtype::IntRect{0, 0, static_cast<int>(m_window->getSize().x), 50});
}

GUISystem::~GUISystem() {}

void GUISystem::updateData(SystemData &t_data) {
  m_event_queue = t_data.event_queue;
}

void GUISystem::update() {
  int total_coins = 0;
  for (EntityID ent : EntityViewer<Player>(*m_em)) {
    Player *player = (*m_em).Get<Player>(ent);
    if (player->player_id == m_clientCom->m_id) {
      m_nb_kills->setString(std::to_string(player->kills));
      m_nb_exp->setString(std::to_string(player->exp));
      m_nb_exp->setPosition(
        {static_cast<float>(m_window->getSize().x -
                            (m_nb_exp->getLocalBounds().width + 10)),
         static_cast<float>(m_window->getSize().y - 40)});
      m_exp->setPosition(
        {static_cast<float>(m_window->getSize().x -
                            (m_nb_exp->getLocalBounds().width + 20 +
                             m_exp->getLocalBounds().width)),
         static_cast<float>(m_window->getSize().y - 40)});
      m_nb_coins->setString(std::to_string(player->coins));
      m_nb_bomb_shots->setString(std::to_string(player->bomb_shot) + "x");
      m_nb_fire_shots->setString(std::to_string(player->fire_shot) + "x");
      m_nb_money_shots->setString(std::to_string(player->coin_shot) + "x");
    }
    total_coins += player->coins;
  }
  m_nb_total_coins->setString(std::to_string(total_coins) + " (Total)");
  m_window->draw(m_bg);
  m_window->draw(m_coin);
  m_window->draw(m_nb_coins);
  m_window->draw(m_kills);
  m_window->draw(m_nb_kills);
  m_window->draw(m_exp);
  m_window->draw(m_nb_exp);
  m_window->draw(m_bomb);
  m_window->draw(m_fire);
  m_window->draw(m_second_coin);
  m_window->draw(m_money);
  m_window->draw(m_nb_money_shots);
  m_window->draw(m_nb_bomb_shots);
  m_window->draw(m_nb_fire_shots);
  m_window->draw(m_nb_total_coins);
}
