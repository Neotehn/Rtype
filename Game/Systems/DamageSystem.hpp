#ifndef CLIENT_SRC_SYSTEMS_DAMAGESYSTEM_HPP_
#define CLIENT_SRC_SYSTEMS_DAMAGESYSTEM_HPP_

#include <string>
#include <memory>

#include "../ECS/DataTypesECS.hpp"
#include "../ECS/ISystem.hpp"
#include "../../Client/src/Action/Action.hpp"
#include "../../Client/src/Action/StateAction.hpp"
#include "../../Client/src/InputManager/InputManager.hpp"
#include "./SoundSystem.hpp"

class DamageSystem : public ISystem {
 public:
  DamageSystem(std::shared_ptr<EntityManager> t_em,
               InputManager &t_client_input_manager, std::size_t t_port_number,
               bool &t_is_running,
               std::vector<SoundSystem::SoundType> &t_sounds);
  ~DamageSystem();

  virtual void update();
  virtual void updateData(SystemData &t_data);

 private:
  EventQueue m_event_queue;
  InputManager &m_client_input_manager;
  std::size_t m_port_number;
  bool &m_is_running;
  std::vector<SoundSystem::SoundType> &m_play_sounds;
};

#endif  // CLIENT_SRC_SYSTEMS_DAMAGESYSTEM_HPP_
