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
                     rtype::IRenderWindow *t_window) {
  m_em = t_em;
  m_graphic_loader = t_graphic_loader;
  m_window = t_window;
  initText();
  SpriteECS sprite =
    SpriteECS("./../Client/sprites/powerup/coin.png", t_graphic_loader);
  m_coin = m_graphic_loader->loadRectangleShape();
  m_coin->setSize({30, 30});
  m_coin->setPosition({10, static_cast<float>(m_window->getSize().y - 40)});
  m_coin->setTexture(sprite.getTexture());
  m_coin->setTextureRect(rtype::IntRect{0, 0, 84, 84});

  m_bg = m_graphic_loader->loadRectangleShape();
  m_bg->setSize({static_cast<float>(m_window->getSize().x), 50});
  m_bg->setPosition({0, static_cast<float>(m_window->getSize().y - 50)});
  SpriteECS spritebg =
    SpriteECS("./../Client/assets/bg_stats.png", t_graphic_loader);
  m_bg->setTexture(spritebg.getTexture());
  m_bg->setTextureRect(
    rtype::IntRect{0, 0, static_cast<int>(m_window->getSize().x), 50});
}

GUISystem::~GUISystem() {}

void GUISystem::updateData(SystemData &t_data) {
  m_event_queue = t_data.event_queue;
}

void GUISystem::update() {
  for (std::shared_ptr<Action> action :
       m_event_queue.getAllOfType(Action::ActionType::INCREASE)) {
    Action::IncreaseType type = action->getIncreaseType();
    Player *player;
    switch (type) {
      case Action::IncreaseType::KILLS:
        player = (*m_em.get()).Get<Player>(action->getId());
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
        break;
      case Action::IncreaseType::FIRE_SHOT:
        player = (*m_em.get()).Get<Player>(action->getId());
        break;
      case Action::IncreaseType::BOMB_SHOT:
        player = (*m_em.get()).Get<Player>(action->getId());
        break;
      case Action::IncreaseType::COINS:
        player = (*m_em.get()).Get<Player>(action->getId());
        m_nb_coins->setString(std::to_string(player->coins));
        break;
      default:
        break;
    }
  }
  m_window->draw(m_bg);
  m_window->draw(m_coin);
  m_window->draw(m_nb_coins);
  m_window->draw(m_kills);
  m_window->draw(m_nb_kills);
  m_window->draw(m_exp);
  m_window->draw(m_nb_exp);
}