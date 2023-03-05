#include "RaylibWindow.hpp"
#include <iostream>

namespace rtype {

  RaylibWindow::RaylibWindow() {}

  RaylibWindow::RaylibWindow(unsigned int t_width, unsigned int t_height,
                             std::string t_title) {
    InitWindow(t_width, t_height, t_title.c_str());
    SetTargetFPS(60);
  }

  RaylibWindow::~RaylibWindow() { CloseWindow(); }

  void RaylibWindow::draw(const rtype::ISprite *t_sprite) {
    rtype::ISprite *sprite = const_cast<rtype::ISprite *>(t_sprite);
    rtype::RaylibSprite *raylibSprite =
      dynamic_cast<rtype::RaylibSprite *>(sprite);
    rtype::ITexture *raylibITexture =
      const_cast<rtype::ITexture *>(raylibSprite->getTexture());
    rtype::RaylibTexture *raylibTexture =
      dynamic_cast<rtype::RaylibTexture *>(raylibITexture);

    IntRect rect = raylibSprite->getTextureRect();
    Rectangle rectangle = {
      static_cast<float>(rect.left), static_cast<float>(rect.top),
      static_cast<float>(rect.width), static_cast<float>(rect.height)};
    rtype::Vector2f origin = raylibSprite->getOrigin();
    rtype::Vector2f position = raylibSprite->getPosition();
    rtype::Vector2f scale = raylibSprite->getScale();
    rtype::Color color = raylibSprite->getColor();
    Texture texture = *const_cast<Texture *>(raylibTexture->getTexture());

    DrawTextureEx(texture, {position.x, position.y},
                  raylibSprite->getRotation(), scale.x,
                  {color.r, color.g, color.b, color.a});
  }

  void RaylibWindow::draw(rtype::IRectangleShape *t_shape) {
    rtype::IRectangleShape *shape =
      const_cast<rtype::IRectangleShape *>(t_shape);
    rtype::RaylibRectangleShape *raylibShape =
      dynamic_cast<rtype::RaylibRectangleShape *>(shape);
    rtype::RaylibTexture *raylibTexture = raylibShape->getTexture();
    IntRect rect = raylibShape->getTextureRect();
    Rectangle rectangle = {
      static_cast<float>(rect.left), static_cast<float>(rect.top),
      static_cast<float>(rect.width), static_cast<float>(rect.height)};
    rtype::Vector2f origin = raylibShape->getOrigin();
    rtype::Vector2f position = raylibShape->getPosition();
    rtype::Vector2f scale = raylibShape->getScale();
    rtype::Color color = raylibTexture->getColor();
    Texture texture = *const_cast<Texture *>(raylibTexture->getTexture());

    DrawTextureEx(texture, {position.x, position.y}, raylibShape->getRotation(),
                  scale.x, {color.r, color.g, color.b, color.a});
    //    DrawTextureTiled(texture, rectangle, rectangle, {origin.x, origin.y},
    //                     raylibShape->getRotation(), scale.x,
    //                     {color.r, color.g, color.b, color.a});
  }

  void RaylibWindow::draw(const rtype::IText *t_text) {
    rtype::IText *text = const_cast<rtype::IText *>(t_text);
    rtype::RaylibText *raylibText = dynamic_cast<rtype::RaylibText *>(text);
    rtype::Color color = raylibText->getColor();
    DrawText(t_text->getString().c_str(), t_text->getPosition().x,
             t_text->getPosition().y, t_text->getCharacterSize(),
             {color.r, color.g, color.b, color.a});
  }

  void RaylibWindow::display() { EndDrawing(); }

  rtype::Vector2u RaylibWindow::getSize() const {
    return rtype::Vector2u{static_cast<unsigned int>(GetScreenWidth()),
                           static_cast<unsigned int>(GetScreenHeight())};
  }

  bool RaylibWindow::isOpen() { return !WindowShouldClose(); }

  void RaylibWindow::close() { CloseWindow(); }

  void RaylibWindow::clear(rtype::Color t_color) {
    BeginDrawing();
    ClearBackground({t_color.r, t_color.g, t_color.b, t_color.a});
  }

  void RaylibWindow::setFramerateLimit(unsigned int t_fps) {
    SetTargetFPS(t_fps);
  }

  void RaylibWindow::create(unsigned int t_width, unsigned int t_height,
                            std::string t_title) {
    InitWindow(t_width, t_height, t_title.c_str());
    SetTargetFPS(60);
  }

  void RaylibWindow::create(unsigned int t_width, unsigned int t_height,
                            std::string t_title, rtype::Style t_style) {
    InitWindow(t_width, t_height, t_title.c_str());
    SetTargetFPS(60);
  }

  Event createEvent(rtype::EventType t_type, rtype::EventKey t_key) {
    Event event;
    event.type = t_type;
    event.key = t_key;
    return event;
  }

  void RaylibWindow::getTextEntered(rtype::Event &t_event) {
    if (IsKeyPressed(KEY_A)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::A));
    }
    if (IsKeyPressed(KEY_B)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::B));
    }
    if (IsKeyPressed(KEY_C)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::C));
    }
    if (IsKeyPressed(KEY_D)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::D));
    }
    if (IsKeyPressed(KEY_E)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::E));
    }
    if (IsKeyPressed(KEY_F)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::F));
    }
    if (IsKeyPressed(KEY_G)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::G));
    }
    if (IsKeyPressed(KEY_H)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::H));
    }
    if (IsKeyPressed(KEY_I)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::I));
    }
    if (IsKeyPressed(KEY_J)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::J));
    }
    if (IsKeyPressed(KEY_K)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::K));
    }
    if (IsKeyPressed(KEY_L)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::L));
    }
    if (IsKeyPressed(KEY_M)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::M));
    }
    if (IsKeyPressed(KEY_N)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::N));
    }
    if (IsKeyPressed(KEY_O)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::O));
    }
    if (IsKeyPressed(KEY_P)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::P));
    }
    if (IsKeyPressed(KEY_Q)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::Q));
    }
    if (IsKeyPressed(KEY_R)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::R));
    }
    if (IsKeyPressed(KEY_S)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::S));
    }
    if (IsKeyPressed(KEY_T)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::T));
    }
    if (IsKeyPressed(KEY_U)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::U));
    }
    if (IsKeyPressed(KEY_V)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::V));
    }
    if (IsKeyPressed(KEY_W)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::W));
    }
    if (IsKeyPressed(KEY_X)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::X));
    }
    if (IsKeyPressed(KEY_Y)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::Y));
    }
    if (IsKeyPressed(KEY_Z)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::Z));
    }
    if (IsKeyPressed(Num0)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::Num0));
    }
    if (IsKeyPressed(Num1)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::Num1));
    }
    if (IsKeyPressed(Num2)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::Num2));
    }
    if (IsKeyPressed(Num3)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::Num3));
    }
    if (IsKeyPressed(Num4)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::Num4));
    }
    if (IsKeyPressed(Num5)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::Num5));
    }
    if (IsKeyPressed(Num6)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::Num6));
    }
    if (IsKeyPressed(Num7)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::Num7));
    }
    if (IsKeyPressed(Num8)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::Num8));
    }
    if (IsKeyPressed(Num9)) {
      m_events.push_back(createEvent(EventType::TextEntered, EventKey::Num9));
    }
  }

  void RaylibWindow::collectEvents(Event &t_event, Vector2i t_mouse_pos) {
    if (WindowShouldClose()) {
      m_events.push_back(createEvent(EventType::Closed, EventKey::Left));
    }
    if (IsKeyPressed(KEY_W)) {
      m_events.push_back(createEvent(EventType::KeyPressed, EventKey::Up));
    }
    if (IsKeyPressed(KEY_S)) {
      m_events.push_back(createEvent(EventType::KeyPressed, EventKey::Down));
    }
    if (IsKeyPressed(KEY_A)) {
      m_events.push_back(createEvent(EventType::KeyPressed, EventKey::Left));
    }
    if (IsKeyPressed(KEY_D)) {
      m_events.push_back(createEvent(EventType::KeyPressed, EventKey::Right));
    }
    if (IsKeyPressed(KEY_SPACE)) {
      m_events.push_back(createEvent(EventType::KeyPressed, EventKey::Space));
    }
    if (IsKeyPressed(KEY_ENTER)) {
      m_events.push_back(createEvent(EventType::KeyPressed, EventKey::Enter));
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
      m_events.push_back(createEvent(EventType::KeyPressed, EventKey::Escape));
    }

    if (IsKeyReleased(KEY_SPACE)) {
      m_events.push_back(createEvent(EventType::KeyReleased, EventKey::Space));
    }
    if (IsKeyReleased(KEY_ENTER)) {
      m_events.push_back(createEvent(EventType::KeyReleased, EventKey::Enter));
    }
    if (IsKeyReleased(KEY_B)) {
      m_events.push_back(createEvent(EventType::KeyReleased, EventKey::B));
    }
    if (IsKeyReleased(KEY_M)) {
      m_events.push_back(createEvent(EventType::KeyReleased, EventKey::M));
    }
    if (IsKeyReleased(KEY_N)) {
      m_events.push_back(createEvent(EventType::KeyReleased, EventKey::N));
    }
    if (IsKeyReleased(KEY_U)) {
      m_events.push_back(createEvent(EventType::KeyReleased, EventKey::U));
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      m_events.push_back(
        createEvent(EventType::MouseButtonPressed, EventKey::Left));
    }
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
      m_events.push_back(
        createEvent(EventType::MouseButtonPressed, EventKey::Right));
    }
    if (IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON)) {
      m_events.push_back(
        createEvent(EventType::MouseButtonPressed, EventKey::Left));
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_SIDE)) {
      m_events.push_back(
        createEvent(EventType::MouseButtonPressed, EventKey::Left));
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_EXTRA)) {
      m_events.push_back(
        createEvent(EventType::MouseButtonPressed, EventKey::Left));
    }
    if (GetMouseWheelMove() != 0) {
      m_events.push_back(
        createEvent(EventType::MouseWheelMoved, EventKey::Left));
    }
    Vector2 mouse_pos = GetMousePosition();
    if (t_mouse_pos.x != mouse_pos.x || t_mouse_pos.y != mouse_pos.y) {
      m_events.push_back(createEvent(EventType::MouseMoved, EventKey::Left));
    }
    getTextEntered(t_event);
  }

  bool RaylibWindow::pollEvent(rtype::Event &t_event,
                               rtype::Vector2i t_mouse_pos, bool first) {
    if (m_events.empty() && first) { collectEvents(t_event, t_mouse_pos); }
    if (m_events.empty()) { return false; }
    rtype::Event event = m_events.back();
    m_events.pop_back();
    t_event = event;
    return true;
  }
}  // namespace rtype