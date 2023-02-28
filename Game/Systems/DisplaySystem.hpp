#ifndef CLIENT_SRC_SYSTEMS_IDISPLAY_HPP_
#define CLIENT_SRC_SYSTEMS_IDISPLAY_HPP_

#include "../ECS/ISystem.hpp"
#include "../Encapsulation/IRenderWindow.hpp"

class DisplaySystem : public ISystem {
 public:
  DisplaySystem(std::shared_ptr<EntityManager> t_em,
                rtype::IRenderWindow *t_window);
  ~DisplaySystem();

  virtual void update();
  virtual void updateData(SystemData &t_data);

 private:
  rtype::IRenderWindow *m_window;
};

#endif  // CLIENT_SRC_SYSTEMS_IDISPLAY_HPP_
