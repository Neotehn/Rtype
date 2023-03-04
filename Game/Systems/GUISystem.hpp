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
#include "../../Client/Protocol/UdpClient.hpp"

class GUISystem : public ISystem {
 public:
  GUISystem(std::shared_ptr<EntityManager> t_em,
            rtype::IGraphicLoader *t_graphic_loader,
            rtype::IRenderWindow *t_window, UdpClient *t_clientCom);
  ~GUISystem();
  void update();
  void updateData(SystemData &t_data);

 private:
  EventQueue m_event_queue;
  rtype::IGraphicLoader *m_graphic_loader;
  rtype::IRectangleShape *m_bg;
  rtype::IRectangleShape *m_coin;
  rtype::IRectangleShape *m_second_coin;
  rtype::IRectangleShape *m_fire;
  rtype::IRectangleShape *m_bomb;
  rtype::IRectangleShape *m_money;
  rtype::IFont *m_font;
  rtype::IText *m_nb_coins;
  rtype::IText *m_nb_total_coins;
  rtype::IText *m_nb_bomb_shots;
  rtype::IText *m_nb_fire_shots;
  rtype::IText *m_nb_money_shots;
  rtype::IText *m_nb_kills;
  rtype::IText *m_kills;
  rtype::IText *m_exp;
  rtype::IText *m_nb_exp;
  rtype::IRenderWindow *m_window;
  UdpClient *m_clientCom;

  void initText();
};

#endif /* !GUISYSTEM_HPP_ */
