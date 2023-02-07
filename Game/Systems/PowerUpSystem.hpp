#ifndef R_TYPE_CLIENT_POWERUPSYSTEM_HPP
#define R_TYPE_CLIENT_POWERUPSYSTEM_HPP

#include <memory>

#include "../ECS/ISystem.hpp"
#include "./SoundSystem.hpp"

class PowerUpSystem : public ISystem {
 public:
  PowerUpSystem(std::shared_ptr<EntityManager> t_em,
                std::vector<SoundSystem::SoundType> &t_sounds);
  ~PowerUpSystem();

  void update();
  void updateData(SystemData &t_data);

 private:
  EventQueue m_event_queue;
  std::vector<SoundSystem::SoundType> &m_play_sounds;

  void increaseHealth(std::shared_ptr<Action> action);
};

#endif  //R_TYPE_CLIENT_POWERUPSYSTEM_HPP
