#ifndef CLIENT_SRC_SYSTEMS_IDISPLAY_HPP_
#define CLIENT_SRC_SYSTEMS_IDISPLAY_HPP_

#include "../ECS/ISystem.hpp"
#include "../Encapsulation/IRenderWindow.hpp"
#include "GUISystem.hpp"

class DisplaySystem : public ISystem {
 public:
  DisplaySystem(std::shared_ptr<EntityManager> t_em,
                rtype::IRenderWindow *t_window);
  ~DisplaySystem() = default;

  virtual void update() override;
  virtual void updateData(SystemData &t_data) override;

 private:
  rtype::IRenderWindow *m_window;
  GUISystem m_gui;
  std::size_t m_flag;
  EventQueue m_event_queue;
};

#endif  // CLIENT_SRC_SYSTEMS_IDISPLAY_HPP_
