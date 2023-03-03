/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** GUISystem
*/

#ifndef GUISYSTEM_HPP_
#define GUISYSTEM_HPP_

#include <memory>

#include "../ECS/ISystem.hpp"
#include "./SoundSystem.hpp"
#include "../Encapsulation/IFont.hpp"
#include "../Encapsulation/IText.hpp"

class GUISystem : public ISystem {
 public:
  GUISystem(std::shared_ptr<EntityManager> t_em,
            rtype::IGraphicLoader *t_graphic_loader,
            rtype::IRenderWindow *t_window);
  ~GUISystem();
  void update();
  void updateData(SystemData &t_data);

 private:
  EventQueue m_event_queue;
  rtype::IGraphicLoader *m_graphic_loader;
  rtype::IRectangleShape *m_bg;
  rtype::IRectangleShape *m_coin;
  rtype::IFont *m_font;
  rtype::IText *m_nb_coins;
  rtype::IText *m_nb_kills;
  rtype::IText *m_kills;
  rtype::IText *m_exp;
  rtype::IText *m_nb_exp;
  rtype::IRenderWindow *m_window;

  void initText();
};

#endif /* !GUISYSTEM_HPP_ */
