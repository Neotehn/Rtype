#ifndef R_TYPE_CLIENT_GRAPHICDATATYPES_HPP
#define R_TYPE_CLIENT_GRAPHICDATATYPES_HPP

namespace rtype {
  struct Vector2f {
    float x = 0;
    float y = 0;

    Vector2f &operator=(const Vector2f &t_vector) {
      x = t_vector.x;
      y = t_vector.y;
      return *this;
    }

    Vector2f &operator+=(const Vector2f &t_vector) {
      x += t_vector.x;
      y += t_vector.y;
      return *this;
    }

    Vector2f &operator*(const float &t_factor) {
      x *= t_factor;
      y *= t_factor;
      return *this;
    }
    Vector2f &operator*=(const float &t_factor) {
      x *= t_factor;
      y *= t_factor;
      return *this;
    }
    bool operator!=(const Vector2f &t_vector) {
      return (x != t_vector.x || y != t_vector.y);
    }
  };

  struct Vector2u {
    unsigned int x;
    unsigned int y;
  };

  struct Vector2i {
    int x;
    int y;
  };

  struct IntRect {
    int left;
    int top;
    int width;
    int height;
  };

  struct FloatRect {
    float left;
    float top;
    float width;
    float height;
  };

  struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
  };

  static const Color Black = {0, 0, 0, 255};
  static const Color White = {255, 255, 255, 255};
  static const Color Red = {255, 0, 0, 255};
  static const Color Green = {0, 255, 0, 255};
  static const Color Blue = {0, 0, 255, 255};
  static const Color Yellow = {255, 255, 0, 255};
  static const Color Magenta = {255, 0, 255, 255};
  static const Color Cyan = {0, 255, 255, 255};
  static const Color Transparent = {0, 0, 0, 0};

  enum Style {
    None = 0,
    Titlebar = 1 << 0,
    Resize = 1 << 1,
    Close = 1 << 2,
    Fullscreen = 1 << 3,

    Default = Titlebar | Resize | Close
  };

}  // namespace rtype
#endif  //R_TYPE_CLIENT_GRAPHICDATATYPES_HPP
