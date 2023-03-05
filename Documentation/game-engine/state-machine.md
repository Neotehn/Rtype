# State Machine

In order to manage all different screens, like the different menus and the game screen, we decided to implement a state machine.&#x20;

The state machine is split up in different classes. The most important are the "StateMachine" and the "State" class. The "StateMachine"-Class contains the stack of states and the "State"-Class builds the base of all screens. &#x20;

<figure><img src="../assets/Screenshot from 2023-01-31 14-44-03.png" alt=""><figcaption></figcaption></figure>

To add a new screen you simply have to create a new class like the "ScreenStates"-Class in the following picture. The "update"-function contains event management, the "draw"-function contains everything relevant to display the scene. The new scene should be put inside the "States"-folder, which you find under "GameEngine" -> "src".

Example:

CustomState.hpp:

```
1  #ifndef CUSTOMSTATE_HPP_
2  #define CUSTOMSTATE_HPP_
3 
4  #include <SFML/Graphics/RenderWindow.hpp>
5  #include <SFML/Graphics/Sprite.hpp>
6  #include <SFML/Graphics/Texture.hpp>
7  #include <SFML/Window/Event.hpp>
8  
9  #include "{PATH_TO_FILE}/MusicPlayer.hpp"
10 #include "{PATH_TO_FILE}/State.hpp"
11 #incldue "{PATH_TO_FILE}/StateMachine.hpp"
12 
13 class CustomState final : public State {
14    public:
15        CustomState(StateMachine &t_machine, rtype::IRenderWindow *t_window,
16                               MusicPlayer &t_music_player, std::size_t T_flag,
17                               bool t_replace = true);
18        void update() override;
19        void draw() override;
20        
21    private:    
22        rtype::ITexture *m_bg_t;
23        rtype::ISprite *m_bg_s;
24        std::size_t m_flag;
25 };        
26        
27 #endif /* !CUSTOMSTATE_HPP_ */
```

CustomState.cpp:

```
  #include "{PATH_TO_FILE}/CustomState.hpp"
  #include "{PATH_TO_FILE}/MainState.hpp" 
  #include "{PATH_TO_FILE}/SettingsState.hpp"
  // or add other states

  CustomState::CustomState(StateMachine &t_machine, rtype::IRenderWindow *t_window,
                          MusicPlayer &t_music_player, std::size_t T_flag,
                          bool t_replace = true)
        : State(t_machine, t_window, t_music_player, t_replace), 
         m_flag(t_flag) {
     m_bg_t = new rtype::Texture();
     m_bg_s = new rtype::Sprite();
     if (!m_bg_t->loadFromFile("{PATH_TO_FILE}/{IMAGE_NAME}.{png/jpg}")) {
         throw std::runtime_error("Unable to load image.");
     };
     float size_x = m_window->getSize().x;
     float size_y = m_window->getSize().y;
     float scale_x = size_x / m_bg_t->getSize().x;
     float scale_y = size_y / m_bg_t->getSize().y;
     m_bg_s->setTexture(m_bg_t, true);
     m_bg_s->setScale({scale_x, scale_y});
     m_music_player.play(MusicID::{MUSIC_NAME});
 }

  void MainState::update() {
     for (auto event = rtype::Event{}; m_window->pollEvent(event);) {
         sf::Vector2i mouse_pos = m_mouse->getMousePosition(m_window);
         sf::Vector2f mouse_pos_f(static_cast(mouse_pos.x),
                                  static_cast(mouse_pos.y));
         switch (event.type) {
             case rtype::EventType::Closed:
                 m_state_machine.quit();
                 break;
             case rtype::EventType::KeyPressed:
                 switch (event.key.code) {
                     case rtype::EventKey::Escape:
                         m_state_machine.quit();
                         break;
                     default:
                         break;
                 }
                 break;
             default:
                 break;
        }
     }
 } 

 void CustomState::draw() {
     m_window->clear();
     m_window->draw(m_bg_s);
     m_window->display();
 }

```



[Back](../overview/game-engine.md)
