#ifndef R_TYPE_CLIENT_ISOUND_HPP
#define R_TYPE_CLIENT_ISOUND_HPP

#include <string>
#include <vector>

namespace rtype {
  class ISounds {
   public:
    virtual ~ISounds() = default;

    virtual bool addSoundFromFile(const std::string &t_path) = 0;
    virtual void play(int t_index) = 0;
    virtual void stop(int t_index) = 0;
    virtual void pause(int t_index) = 0;
    virtual void setVolume(float t_volume) = 0;
    virtual float getVolume(int t_index) = 0;
    virtual void setVolume(int t_index, float t_vol) = 0;

    // private: vector of all sounds in the inherited class
  };
}  // namespace rtype

#endif  //R_TYPE_CLIENT_ISOUND_HPP
