#include "Init.hpp"
#include <string>
#include <vector>

EntityID initPlayer(std::shared_ptr<EntityManager> t_entity_manager,
                    UdpServer *t_serverCom) {
  EntityID player = t_entity_manager->createNewEntity();

  SpriteECS player_sprite = SpriteECS("../Client/sprites/starship.png");

  Pos player_pos = Pos{rtype::Vector2f{0.0, 0.0}, rtype::Vector2f{300, 300}};

  rtype::IRectangleShape *body = new rtype::RectangleShape();
  body->setSize({200, 200});
  body->setPosition({player_pos.position.x, player_pos.position.y});
  body->setTexture(player_sprite.getTexture());
  body->setRotation(90.0);

  Health health = initPlayerHealthBar();
  Player player_obj = Player{player_sprite, player_pos, body, health, 10};
  t_entity_manager->Assign<Player>(player, player_obj);
  t_serverCom->addEvent(std::make_shared<Action>(
    CreateAction(player, Action::ObjectType::PLAYER, player_pos.position,
                 "../Client/sprites/starship.png")));
  return player;
}

void initBackground(EntityManager &t_entity_manager) {
  // background layer 1
  EntityID background1 = t_entity_manager.createNewEntity();
  BackgroundLayer background_layer1 =
    BackgroundLayer{SpriteECS("../Client/sprites/background/bg1.png", {5, 5}),
                    rtype::Vector2f{0, 0}, 1, (-272 * 5)};
  t_entity_manager.Assign<BackgroundLayer>(background1, background_layer1);

  // background layer 2
  EntityID background2 = t_entity_manager.createNewEntity();
  BackgroundLayer background_layer2 =
    BackgroundLayer{SpriteECS("../Client/sprites/background/bg2.png", {4, 4}),
                    rtype::Vector2f{0, 160}, 2, (-272 * 10)};
  t_entity_manager.Assign<BackgroundLayer>(background2, background_layer2);

  // background layer 3
  EntityID background3 = t_entity_manager.createNewEntity();
  BackgroundLayer background_layer3 =
    BackgroundLayer{SpriteECS("../Client/sprites/background/bg3.png", {5, 5}),
                    rtype::Vector2f{0, 0}, 3, (-272 * 5)};
  t_entity_manager.Assign<BackgroundLayer>(background3, background_layer3);
}

Health initPlayerHealthBar() {
  SpriteECS player_health_bar_sprite_full =
    SpriteECS("../Client/sprites/playerassets/Fulllife.png");

  Pos bar_pos = Pos{rtype::Vector2f{0, 0}, rtype::Vector2f{120, 230}};

  HealthBar bar_stats =
    HealthBar{std::vector<std::string>{
                std::string("../Client/sprites/playerassets/ouch 3x.png"),
                std::string("../Client/sprites/playerassets/ouch 2x.png"),
                std::string("../Client/sprites/playerassets/ouch.png"),
                std::string("../Client/sprites/playerassets/Fulllife.png")},
              3};

  rtype::IRectangleShape *body = new rtype::RectangleShape();
  body->setSize({126, 42});
  body->setPosition({bar_pos.position.x, bar_pos.position.y});
  body->setTexture(player_health_bar_sprite_full.getTexture());

  return Health{bar_stats, bar_pos, body};
}

//void initEnemy()
