#include "RaylibWindow.hpp"

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
    rtype::Vector2f scale = raylibSprite->getScale();
    rtype::Color color = raylibSprite->getColor();
    Texture texture = *const_cast<Texture *>(raylibTexture->getTexture());

    DrawTextureTiled(texture, rectangle, rectangle, {origin.x, origin.y},
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
    rtype::Vector2f scale = raylibShape->getScale();
    rtype::Color color = raylibTexture->getColor();
    Texture texture = *const_cast<Texture *>(raylibTexture->getTexture());

    DrawTextureTiled(texture, rectangle, rectangle, {origin.x, origin.y},
                     raylibShape->getRotation(), scale.x,
                     {color.r, color.g, color.b, color.a});
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

  bool RaylibWindow::pollEvent(rtype::Event &t_event) {
    if (IsKeyPressed(KEY_W)) {
      t_event.type = EventType::KeyPressed;
      t_event.key = EventKey::Up;
      return true;
    }
    if (IsKeyPressed(KEY_S)) {
      t_event.type = EventType::KeyPressed;
      t_event.key = rtype::EventKey::Down;
      return true;
    }
    if (IsKeyPressed(KEY_A)) {
      t_event.type = EventType::KeyPressed;
      t_event.key = rtype::EventKey::Left;
      return true;
    }
    if (IsKeyPressed(KEY_D)) {
      t_event.type = EventType::KeyPressed;
      t_event.key = rtype::EventKey::Right;
      return true;
    }
    if (IsKeyPressed(KEY_SPACE)) {
      t_event.type = EventType::KeyPressed;
      t_event.key = rtype::EventKey::Space;
      return true;
    }
    if (IsKeyPressed(KEY_ENTER)) {
      t_event.type = EventType::KeyPressed;
      t_event.key = rtype::EventKey::Enter;
      return true;
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
      t_event.type = EventType::KeyPressed;
      t_event.key = rtype::EventKey::Escape;
      return true;
    }

    if (IsKeyReleased(KEY_SPACE)) {
      t_event.type = EventType::KeyReleased;
      t_event.key = rtype::EventKey::Space;
      return true;
    }
    if (IsKeyReleased(KEY_ENTER)) {
      t_event.type = EventType::KeyReleased;
      t_event.key = rtype::EventKey::Enter;
      return true;
    }
    if (IsKeyReleased(KEY_B)) {
      t_event.type = EventType::KeyReleased;
      t_event.key = rtype::EventKey::B;
      return true;
    }
    if (IsKeyReleased(KEY_M)) {
      t_event.type = EventType::KeyReleased;
      t_event.key = rtype::EventKey::M;
      return true;
    }
    if (IsKeyReleased(KEY_N)) {
      t_event.type = EventType::KeyReleased;
      t_event.key = rtype::EventKey::N;
      return true;
    }
    if (IsKeyReleased(KEY_U)) {
      t_event.type = EventType::KeyReleased;
      t_event.key = rtype::EventKey::U;
      return true;
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      t_event.type = EventType::MouseButtonPressed;
      t_event.key = EventKey::Left;
      return true;
    }
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
      t_event.type = EventType::MouseButtonPressed;
      t_event.key = EventKey::Right;
      return true;
    }
    if (IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON)) {
      t_event.type = EventType::MouseButtonReleased;
      t_event.key = EventKey::Left;
      return true;
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_SIDE)) {
      t_event.type = EventType::MouseButtonReleased;
      t_event.key = EventKey::Left;
      return true;
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_EXTRA)) {
      t_event.type = EventType::MouseButtonReleased;
      t_event.key = EventKey::Left;
      return true;
    }
    if (GetMouseWheelMove() != 0) {
      t_event.type = EventType::MouseWheelMoved;
      t_event.key = EventKey::Left;
      return true;
    }
    if (GetMouseDelta().x != 0 || GetMouseDelta().y != 0) {
      t_event.type = EventType::MouseMoved;
      t_event.key = EventKey::Left;
      return true;
    }
    return false;
  }
}  // namespace rtype