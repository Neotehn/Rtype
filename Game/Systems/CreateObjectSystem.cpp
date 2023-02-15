#include "CreateObjectSystem.hpp"

CreateObjectSystem::CreateObjectSystem(
  std::shared_ptr<EntityManager> t_em,
  std::vector<SoundSystem::SoundType> &t_sounds)
    : m_play_sounds(t_sounds) {
  m_em = t_em;
}

CreateObjectSystem::~CreateObjectSystem() {}

void CreateObjectSystem::updateData(SystemData &t_data) {
  m_event_queue = t_data.event_queue;
}

void CreateObjectSystem::update() {
  for (std::shared_ptr<Action> action :
       m_event_queue.getAllOfType(Action::ActionType::CREATE)) {
    Action::ObjectType type = action->getCreateType();
    EntityID id = action->getId();
    sf::Vector2f pos = action->getCreatePosition();
    float velocity = 0;
    switch (type) {
      // TODO: add player creation somewhere to event queue of udp server
      case Action::ObjectType::PLAYER:
        createPlayer(id, action->getCreateSpritePath(), pos);
        break;
      case Action::ObjectType::BULLET:
        createBullet(id, pos);
        break;
      case Action::ObjectType::ENEMY:
        velocity = action->getVelocity();
        std::cout << "Create enemy at pos " << pos.x << " " << pos.y << " "
                  << velocity << std::endl;
        createEnemy(id, pos, velocity);
        break;
      case Action::ObjectType::EXPLOSION:
        createExplosion(id, pos);
        break;
      case Action::ObjectType::POWER_UP:
        createPowerUp(id, pos);
        break;
      default:
        break;
    }
  }
}

void CreateObjectSystem::createPlayer(EntityID t_id, std::string t_sprite_path,
                                      sf::Vector2f t_pos) {
  EntityID player = m_em->createNewEntity(t_id);
  SpriteECS player_sprite = SpriteECS(t_sprite_path);

  Pos player_pos = Pos{sf::Vector2f(0, 0), t_pos};

  sf::RectangleShape body;
  body.setSize({200, 200});
  body.setPosition(player_pos.position);
  body.setTexture(player_sprite.getTexture());
  body.setRotation(90.0);
  body.setOutlineColor(sf::Color::Red);
  Health health = initPlayerHealthBar(player);

  Player player_obj = Player{player_sprite, player_pos, body, health, 10};
  m_em->Assign<Player>(player, player_obj);
}

Health CreateObjectSystem::initPlayerHealthBar(EntityID t_player_id) {
  SpriteECS player_health_bar_sprite_full =
    SpriteECS("../Client/sprites/playerassets/Fulllife.png");

  Pos bar_pos = Pos{sf::Vector2f(0, 0), sf::Vector2f(120, 230)};

  HealthBar bar_stats =
    HealthBar{std::vector<std::string>{
                std::string("../Client/sprites/playerassets/ouch 3x.png"),
                std::string("../Client/sprites/playerassets/ouch 2x.png"),
                std::string("../Client/sprites/playerassets/ouch.png"),
                std::string("../Client/sprites/playerassets/Fulllife.png")},
              3};

  sf::RectangleShape body;
  body.setSize({126, 42});
  body.setPosition(bar_pos.position);
  body.setTexture(player_health_bar_sprite_full.getTexture());

  return Health{bar_stats, bar_pos, body};
}

void CreateObjectSystem::createBullet(EntityID t_id, sf::Vector2f t_pos) {
  EntityID bullet = m_em->createNewEntity(t_id);
  SpriteECS sprite = SpriteECS("./../Client/sprites/shoot2.png");

  sf::RectangleShape bullet_body;
  bullet_body.setSize({20, 20});
  bullet_body.setPosition(t_pos);
  bullet_body.setTexture(sprite.getTexture());

  m_play_sounds.push_back(SoundSystem::SoundType::shoot);
  Bullet displayable_bullet = Bullet{bullet_body, 10.0, t_pos};
  m_em->Assign<Bullet>(bullet, displayable_bullet);
  std::cout << "create bullet" << std::endl;
}

void CreateObjectSystem::createEnemy(EntityID t_id, sf::Vector2f t_pos,
                                     float t_velocity) {
  EntityID enemy = m_em->createNewEntity(t_id);
  SpriteECS sprite = SpriteECS("./../Client/sprites/r-typesheet30a.gif");
  sf::RectangleShape body;
  body.setSize({30, 30});
  body.setPosition(t_pos);
  body.setTexture(sprite.getTexture());
  body.setTextureRect(sf::IntRect(0, 0, 34, 34));

  AnimationObj enemy_obj =
    AnimationObj{"enemy", Pos{{-7, t_velocity}, t_pos},
                 AnimationTime{.current_animation_time = 0,
                               .display_time = 0.1,
                               .last_timer = 0},
                 AnimationRect{.size = 34, .limit = 68}, body};
  m_em->Assign<AnimationObj>(enemy, enemy_obj);
}

void CreateObjectSystem::createExplosion(EntityID t_id, sf::Vector2f t_pos) {
  EntityID explosion = m_em->createNewEntity(t_id);
  SpriteECS sprite = SpriteECS("./../Client/sprites/explosion/Explosion.png");
  sf::RectangleShape body;
  body.setSize({50, 50});
  body.setPosition(t_pos);
  body.setTexture(sprite.getTexture());
  body.setTextureRect(sf::IntRect(0, 0, 96, 96));

  AnimationObj explosion_obj =
    AnimationObj{"explosion", Pos{{0, 0}, t_pos},
                 AnimationTime{.current_animation_time = 0,
                               .display_time = 0.06,
                               .last_timer = 0},
                 AnimationRect{.size = 96, .limit = 1056}, body};
  m_em->Assign<AnimationObj>(explosion, explosion_obj);

  m_play_sounds.push_back(SoundSystem::SoundType::explosion);
}

void CreateObjectSystem::createPowerUp(EntityID t_id, sf::Vector2f t_pos) {
  EntityID powerup = m_em->createNewEntity(t_id);
  SpriteECS sprite = SpriteECS("./../Client/sprites/powerup/coin.png");
  sf::RectangleShape body;
  body.setSize({30, 30});
  body.setPosition(t_pos);
  body.setTexture(sprite.getTexture());
  body.setTextureRect(sf::IntRect(0, 0, 84, 84));

  AnimationObj power_up =
    AnimationObj{"powerup", Pos{{-7, 0}, t_pos},
                 AnimationTime{.current_animation_time = 0,
                               .display_time = 0.1,
                               .last_timer = 0},
                 AnimationRect{.size = 84, .limit = 420}, body};
  m_em->Assign<AnimationObj>(powerup, power_up);
}
