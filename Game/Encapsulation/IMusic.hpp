#ifndef R_TYPE_CLIENT_IMUSIC_HPP
#define R_TYPE_CLIENT_IMUSIC_HPP

namespace rtype {
  class IMusic {
   public:
    virtual ~IMusic() = default;

    virtual bool openFromFile(const std::string &) = 0;
    virtual void setVolume(float) = 0;
    virtual void setLoop(bool) = 0;
    virtual void play() = 0;
    virtual void stop() = 0;
    virtual void pause() = 0;
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_IMUSIC_HPP
