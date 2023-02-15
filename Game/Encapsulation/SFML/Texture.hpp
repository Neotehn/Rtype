#ifndef R_TYPE_CLIENT_TEXTURE_HPP
#define R_TYPE_CLIENT_TEXTURE_HPP

namespace rtype {
  //  class Texture {
  //    public:
  //      enum CoordinateType
  //      {
  //        Normalized, //!< Texture coordinates in range [0 .. 1]
  //        Pixels      //!< Texture coordinates in range [0 .. size]
  //      };
  //
  //      Texture();
  //      Texture(const Texture& copy);
  //      ~Texture();
  //
  //      bool create(unsigned int width, unsigned int height);
  //      bool loadFromFile(const std::string& filename, const IntRect& area = IntRect());
  //      bool loadFromMemory(const void* data, std::size_t size, const IntRect& area = IntRect());
  //      bool loadFromStream(InputStream& stream, const IntRect& area = IntRect());
  //      bool loadFromImage(const Image& image, const IntRect& area = IntRect());
  //      rtype::Vector2u getSize() const;
  //      Image copyToImage() const;
  //      void update(const Uint8* pixels);
  //      void update(const Uint8* pixels, unsigned int width, unsigned int height, unsigned int x, unsigned int y);
  //      void update(const Texture& texture);
  //      void update(const Texture& texture, unsigned int x, unsigned int y);
  //      void update(const Image& image);
  //      void update(const Image& image, unsigned int x, unsigned int y);
  //      void update(const Window& window);
  //      void update(const Window& window, unsigned int x, unsigned int y);
  //      void setSmooth(bool smooth);
  //      bool isSmooth() const;
  //      void setSrgb(bool sRgb);
  //      bool isSrgb() const;
  //      void setRepeated(bool repeated);
  //      bool isRepeated() const;
  //      bool generateMipmap();
  //      Texture& operator =(const Texture& right);
  //      void swap(Texture& right);
  //      unsigned int getNativeHandle() const;
  //      static void bind(const Texture* texture, CoordinateType coordinateType = Normalized);
  //      static unsigned int getMaximumSize();
  //
  //  private:
  //
  //    friend class Text;
  //    friend class RenderTexture;
  //    friend class RenderTarget;
  //
  //    static unsigned int getValidSize(unsigned int size);
  //    void invalidateMipmap();
  //
  //    Vector2u     m_size;          //!< Public texture size
  //    Vector2u     m_actualSize;    //!< Actual texture size (can be greater than public size because of padding)
  //    unsigned int m_texture;       //!< Internal texture identifier
  //    bool         m_isSmooth;      //!< Status of the smooth filter
  //    bool         m_sRgb;          //!< Should the texture source be converted from sRGB?
  //    bool         m_isRepeated;    //!< Is the texture in repeat mode?
  //    mutable bool m_pixelsFlipped; //!< To work around the inconsistency in Y orientation
  //    bool         m_fboAttachment; //!< Is this texture owned by a framebuffer object?
  //    bool         m_hasMipmap;     //!< Has the mipmap been generated?
  //    Uint64       m_cacheId;       //!< Unique number
  //    };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_TEXTURE_HPP
