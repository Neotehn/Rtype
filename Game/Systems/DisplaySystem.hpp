#ifndef CLIENT_SRC_SYSTEMS_IDISPLAY_HPP_
#define CLIENT_SRC_SYSTEMS_IDISPLAY_HPP_

#include "../ECS/ISystem.hpp"
#include "../Encapsulation/IRenderWindow.hpp"
#include "GUISystem.hpp"
#include "../../Client/Protocol/UdpClient.hpp"

class DisplaySystem : public ISystem {
 public:
  DisplaySystem(std::shared_ptr<EntityManager> t_em,
                rtype::IRenderWindow *t_window, std::size_t t_flag,
                rtype::IGraphicLoader *t_graphic_loader,
                UdpClient *m_clientCom = nullptr);
  ./ ~DisplaySystem() = default;

  virtual void update() override;
  virtual void updateData(SystemData &t_data) override;

 private:
  rtype::IRenderWindow *m_window;
  std::size_t m_flag;
  EventQueue m_event_queue;
  GUISystem m_gui;
};

#endif  // CLIENT_SRC_SYSTEMS_IDISPLAY_HPP_
