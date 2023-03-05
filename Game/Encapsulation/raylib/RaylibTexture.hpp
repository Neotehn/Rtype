#ifndef R_TYPE_CLIENT_RAYLIBTEXTURE_HPP
#define R_TYPE_CLIENT_RAYLIBTEXTURE_HPP

#include <raylib.h>

#include "../ITexture.hpp"

namespace rtype {
  class RaylibTexture : public ITexture {
   public:
    RaylibTexture();
    RaylibTexture(const Texture2D &texture);
    ~RaylibTexture() = default;

    bool loadFromFile(const std::string &filename) override;
    bool loadFromFile(const std::string &filename,
                      const IntRect &area = IntRect()) override;

    rtype::Vector2u getSize() const override;

    Texture2D *getTexture();
    const Rectangle &getRect() const;
    void setRect(const Rectangle &t_rect);
    float getRotation() const;
    void setRotation(float t_rotation);
    const Vector2f &getOrigin() const;
    void setOrigin(const Vector2f &t_origin);
    const Vector2f &getPosition() const;
    void setPosition(const Vector2f &t_position);
    const Vector2f &getScale() const;
    void setScale(const Vector2f &t_scale);
    const Color &getColor() const;
    void setColor(const Color &t_color);

    void move(const Vector2f &offset);
    void scale(const Vector2f &factor);
    void rotate(float angle);
    rtype::FloatRect getGlobalBounds();

    Texture *getTexture() const;

   private:
    Texture2D *m_texture;
    Rectangle m_rect = {0, 0, 0, 0};
    float m_rotation = 0;
    Vector2f m_origin = {0, 0};
    Vector2f m_position = {0, 0};
    Vector2f m_scale = {1, 1};
    Vector2f m_size = {1, 1};

   public:
    void setSize(const Vector2f &t_size);

   private:
    Color m_color = {255, 255, 255, 255};
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_RAYLIBTEXTURE_HPP
